#include <Wire.h>
#include <Servo.h>
#include <MPU6050.h>
#include <MS5611.h>
#include <math.h>

#define LAUNCH_DETECT_PIN   PA1
#define STATUS_LED          PB0
#define PYRO_PIN            PB12
#define LANDING_SERVO_PIN   PB2
#define TVC_ROLL_PIN        PB3
#define TVC_PITCH_PIN       PB4
#define ESC1_PIN            PA8
#define ESC2_PIN            PB1

const int MIN_ANGLE = 50;
const int MAX_ANGLE = 130;

const int PWM_MIN = 1000;
const int PWM_MAX = 2000;
const float PEAK_THRUST_N = 30.0f;

const int ESC_IDLE          = 1000;
const int ESC_DESCENT_VALUE = 1150;
const int ESC_OFF           = 900;

const uint32_t THRUST_CURVE_DURATION_MS = 3000;
const float APOGEE_THRESHOLD            = 2.0f;
const uint32_t TOUCHDOWN_TIMEOUT        = 15000;

Servo pitchServo;
Servo rollServo;
Servo legServo;
Servo esc1;
Servo esc2;
MPU6050 mpu;
MS5611 ms5611(0x77);

int32_t ax_offset = 0;
int32_t ay_offset = 0;
float pitch_zero_offset = 0.0f;
float roll_zero_offset  = 0.0f;

float groundPressure = 101325.0f;
float alt_zero_offset = 0.0f;

float maxAltitude = 0.0f;
float descentTriggerAltitude = 0.0f;

uint32_t launchTime = 0;
uint32_t descentStartTime = 0;

bool systemReady    = false;
bool launched       = false;
bool motorCutoff    = false;
bool apogeeDetected = false;
bool descentActive  = false;
bool touchdown      = false;

void computeAnglesDeg(int16_t rawAx, int16_t rawAy, int16_t rawAz, float &pitchDeg, float &rollDeg) {
  float ax = rawAx / 16384.0f;
  float ay = rawAy / 16384.0f;
  float az = rawAz / 16384.0f;

  rollDeg  = atan2(ay, az) * 180.0f / PI;
  pitchDeg = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0f / PI;
}

float getZeroedAltitude() {
  ms5611.read();
  float currentPressure = ms5611.getPressure();
  float rawAlt = ms5611.getAltitude(currentPressure, groundPressure);
  return rawAlt - alt_zero_offset;
}

float getF15ThrustN(float tSec) {
  if (tSec <= 0.0f) {
    return 0.0f;
  } else if (tSec < 0.30f) {
    return (tSec / 0.30f) * 30.0f;
  } else if (tSec < 0.50f) {
    return 30.0f + ((tSec - 0.30f) / 0.20f) * (20.0f - 30.0f);
  } else if (tSec < 1.00f) {
    return 20.0f + ((tSec - 0.50f) / 0.50f) * (18.0f - 20.0f);
  } else if (tSec < 2.00f) {
    return 18.0f + ((tSec - 1.00f) / 1.00f) * (16.7f - 18.0f);
  } else if (tSec < 2.95f) {
    return 16.7f + ((tSec - 2.00f) / 0.95f) * (15.5f - 16.7f);
  } else if (tSec < 3.00f) {
    return 15.5f + ((tSec - 2.95f) / 0.05f) * (0.0f - 15.5f);
  } else {
    return 0.0f;
  }
}

int thrustToPwmUs(float thrustN) {
  float clampedThrust = constrain(thrustN, 0.0f, PEAK_THRUST_N);
  float pwm = PWM_MIN + (clampedThrust / PEAK_THRUST_N) * (PWM_MAX - PWM_MIN);
  return (int)constrain(pwm, PWM_MIN, PWM_MAX);
}

void setup() {
  Wire.begin();

  pinMode(LAUNCH_DETECT_PIN, INPUT_PULLDOWN);
  pinMode(PYRO_PIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(PYRO_PIN, LOW);

  pitchServo.attach(TVC_PITCH_PIN);
  rollServo.attach(TVC_ROLL_PIN);
  legServo.attach(LANDING_SERVO_PIN);
  esc1.attach(ESC1_PIN, PWM_MIN, PWM_MAX);
  esc2.attach(ESC2_PIN, PWM_MIN, PWM_MAX);

  pitchServo.write(90);
  rollServo.write(90);
  legServo.write(90);

  esc1.writeMicroseconds(ESC_IDLE);
  esc2.writeMicroseconds(ESC_IDLE);
  delay(200);

  mpu.initialize();
  bool ms5611OK = ms5611.begin();
  bool mpuOK    = mpu.testConnection();

  if (mpuOK && ms5611OK) {
    systemReady = true;

    int16_t raw_ax, raw_ay, raw_az, raw_gx, raw_gy, raw_gz;
    long sum_ax = 0, sum_ay = 0;
    double sum_pressure = 0.0;
    float sum_pitch = 0.0f, sum_roll = 0.0f;

    const int samples = 200;
    for (int i = 0; i < samples; i++) {
      mpu.getMotion6(&raw_ax, &raw_ay, &raw_az, &raw_gx, &raw_gy, &raw_gz);
      sum_ax += raw_ax;
      sum_ay += raw_ay;

      float p, r;
      computeAnglesDeg(raw_ax, raw_ay, raw_az, p, r);
      sum_pitch += p;
      sum_roll  += r;

      ms5611.read();
      sum_pressure += ms5611.getPressure();
      delay(2);
    }

    ax_offset = sum_ax / samples;
    ay_offset = sum_ay / samples;
    pitch_zero_offset = sum_pitch / samples;
    roll_zero_offset  = sum_roll / samples;

    groundPressure = sum_pressure / samples;
    ms5611.read();
    alt_zero_offset = ms5611.getAltitude(ms5611.getPressure(), groundPressure);
  } else {
    systemReady = false;
  }
}

void loop() {
  uint32_t currentMillis = millis();

  if (!systemReady) {
    digitalWrite(STATUS_LED, (currentMillis % 10000 < 5000) ? HIGH : LOW);
  } else if (!launched) {
    digitalWrite(STATUS_LED, (currentMillis % 1000 < 500) ? HIGH : LOW);
  } else {
    digitalWrite(STATUS_LED, HIGH);
  }

  int16_t raw_ax, raw_ay, raw_az, raw_gx, raw_gy, raw_gz;
  mpu.getMotion6(&raw_ax, &raw_ay, &raw_az, &raw_gx, &raw_gy, &raw_gz);

  int16_t ax = raw_ax - ax_offset;
  int16_t ay = raw_ay - ay_offset;

  float rawPitch, rawRoll;
  computeAnglesDeg(raw_ax, raw_ay, raw_az, rawPitch, rawRoll);
  float zeroedPitch = rawPitch - pitch_zero_offset;
  float zeroedRoll  = rawRoll  - roll_zero_offset;

  float currentAltitude = getZeroedAltitude();

  int pServo, rServo;
  if (abs(zeroedPitch) > 35.0f || abs(zeroedRoll) > 35.0f) {
    pServo = MAX_ANGLE;
    rServo = MAX_ANGLE;
  } else {
    pServo = map((long)(zeroedPitch * 100), -2500, 2500, MIN_ANGLE, MAX_ANGLE);
    rServo = map((long)(zeroedRoll  * 100), -2500, 2500, MIN_ANGLE, MAX_ANGLE);
  }
  pServo = constrain(pServo, MIN_ANGLE, MAX_ANGLE);
  rServo = constrain(rServo, MIN_ANGLE, MAX_ANGLE);

  pitchServo.write(pServo);
  rollServo.write(rServo);

  int currentMotorValue = ESC_IDLE;

  if (!launched && digitalRead(LAUNCH_DETECT_PIN) == HIGH) {
    launched = true;
    launchTime = millis();
  }

  if (launched && !touchdown) {
    if (!motorCutoff) {
      uint32_t elapsedMs = millis() - launchTime;
      float tSec = elapsedMs / 1000.0f;
      currentMotorValue = thrustToPwmUs(getF15ThrustN(tSec));
      if (elapsedMs >= THRUST_CURVE_DURATION_MS) {
        motorCutoff = true;
      }
    }
    else if (!apogeeDetected) {
      currentMotorValue = ESC_IDLE;
      if (currentAltitude > maxAltitude) {
        maxAltitude = currentAltitude;
      }
      if (maxAltitude - currentAltitude > APOGEE_THRESHOLD) {
        apogeeDetected = true;
        descentTriggerAltitude = maxAltitude / 4.0f;
        digitalWrite(PYRO_PIN, HIGH);
      }
    }
    else if (!descentActive) {
      currentMotorValue = ESC_IDLE;
      if (currentAltitude <= descentTriggerAltitude) {
        descentActive = true;
        descentStartTime = millis();
      }
    }
    else {
      currentMotorValue = ESC_DESCENT_VALUE;
      legServo.write(0);

      if (currentAltitude <= 1.2f || (millis() - descentStartTime > TOUCHDOWN_TIMEOUT)) {
        touchdown = true;
      }
    }
  }
  else if (touchdown) {
    currentMotorValue = ESC_OFF;
    digitalWrite(PYRO_PIN, LOW);
  }
  else {
    currentMotorValue = ESC_IDLE;
  }

  esc1.writeMicroseconds(currentMotorValue);
  esc2.writeMicroseconds(currentMotorValue);
}
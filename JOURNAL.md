---
title: "My avionics bay for a vtvl rocket"
github: "https://github.com/kamaleshkrithik03-stack/VTVL-rocket-rep"
description: "This flight controller and sytem is made for my VTVL rocket(vertical takeoff vertical landing) which operates without an actual rocket engine!!"
created_at: "2026-10-21"
total_time: "35h"
---

# October 24, 2026: I started with power diversion

in my experience- having the same powerline as the microcontroller and servos along with pyro channel in a rocket was a bit of a perfect condition for blackout of everything. the best solution i found was to add a cap to 2 different lines from same battery. One is the logic line consisting of my sensors and the black pill(last time it was an arduino nano but i find black pill superior) and another is purely for servos, pyro and the brushless motor.

Timelapse: https://lapse.hackclub.com/timelapse/t8QIn0WJG_cf

**Total time spent: 36m**

# October 27, 2026: I am done with logic power line

In the logic power line i added a lm2596 5v module which along with the 1000mhuf capacitor should keep the black pill and sensors away from a blackout. I've also added a pushbutton between the lm2596 and the black pill to keep the black pill safe from power spikes. Now i have to figure out a way to regulate servo power and brushless motor power.

Timelapse: https://lapse.hackclub.com/timelapse/_zzqxLqfELNa

**Total time spent: 12m**

# October 27, 2026: Done with the schematics(almost)

I am almost done with the schematics and am done with the connections. as you can see- i have replaced the ic lm2596 and xl4015 with a connector pin as i plan on physically placing a pre built version of them on the pcb as it is much easier than to have inductors and whatnot in the pcb in terms of space and replaceabillity(or redundancy). There are also 2 redundant slots in case i have future needs.

![](https://fabricate.hackclub-assets.com/5a56791c9a8460e8c859e8b53fef8bf4b711051bbc67b4966a34fef28a5a5adc/image-jpeg/j%2Chbsjk%2Cfjbf%2Cmxfbjkbjjbjjfb.JPG)

Timelapse: https://lapse.hackclub.com/timelapse/7C_BmZ6xk7Bf

**Total time spent: 1h**

# October 27, 2026: Finished with the schematics

I've replaced the power socket with a screw connecto because i thought that will be better for a VTVL rocket with so much vibrations. I've also added a status LED which can show the state of the rocket. The new pyro channel is for the future in case i decide to switch to a hobby engine instead of a brushless motor.

Timelapse: https://lapse.hackclub.com/timelapse/KaC37svzb_No

**Total time spent: 24m**

# November 17, 2026: assigning the footprints and research on motor

Ive been assigning footprints to the components keeping in mind that it has to handel a lot of current so i tried to take the biggest components(dont know how to phrase it) like 2.54 socket/headers. I also changed the esc power to a screw terminal as normally a esc has t connector but kicad doesnt have that component so next best was a terminal not a socket(what was i thinking). I also was researching on motors and thrust from 3s batteries and a good bldc/prop combo and changing it in the bom

Timelapse: https://lapse.hackclub.com/timelapse/w6HWBbpkSGLw

**Total time spent: 1h 30m**

# November 17, 2026: I did start with pcb ediitor

the pcb editor is so stressful like the nest is just confusing me now i have to start with the traces and im not sure if im doing it right.

Timelapse: https://lapse.hackclub.com/timelapse/nV1OmsoraC4K

**Total time spent: 1h**

# November 17, 2026: took out exact measurements for the pcb

I took out the exact measuremnts from google for d btw pins in the bucks and the black pill so i could try to make the pcb smaller.

Timelapse: https://lapse.hackclub.com/timelapse/dq6kU1n_zOBe

**Total time spent: 54m**

# November 17, 2026: added traces and more research

ive added traces and i cant just seem to find a way fro the last one ughhh. i dont know if i have to add another layer.

Timelapse: https://lapse.hackclub.com/timelapse/E-rpeMPYDdRp

**Total time spent: 1h 6m**

# November 17, 2026: Finished traces

ive finished the traces and also i gave some screw holes for mounting. It is withen my 8cm limit the pcb so im onk and also i added some labels. Now like debugging i have to do it in pcb.

![](https://fabricate.hackclub-assets.com/b3ad2fd9e29a5531917be4a69695d7af6c646d34b73d2ce1ba059da09db9c28c/image-jpeg/yayaya.JPG)

Timelapse: https://lapse.hackclub.com/timelapse/vk8ZdZCFb5v7

**Total time spent: 30m**

# November 17, 2026: added a ground pour

i added a ground pour and fixed a few issues. I still have to check connection but im done with the pcb i think. But oh yeah i need to calc trace width that is a problem

Timelapse: https://lapse.hackclub.com/timelapse/s479jYGN6bPB

**Total time spent: 30m**

# November 18, 2026: I did the TVC design

Ive made a TVC gimbal and to be clear this is a remodel and ive been iterating over the years for this so sorry for the lack of lapse. I can show the iterations if requested.Next i have to check the PCB and also have to design a bldc holder. Since ive been at this over 15 to 16 iterations I think 10hrs is justified as it could most certainly be more.

Timelapse: https://lapse.hackclub.com/timelapse/F4BLoc0F7RdY

**Total time spent: 10h 12m**

# November 18, 2026: GND reroutes

i plan on having 2 bldc and so the traces need to be huge. I plan on having a filled zone for the esc power/bldc power and servo and also i deleted the gnd traces as i have a gnd pour now.

Timelapse: https://lapse.hackclub.com/timelapse/eLj9stN6n3ZN

**Total time spent: 54m**

# November 18, 2026: Ran a drc wit so many issues

researching why rat nets appear even with vias(turns out i just had to reload). I also plan on addind a nrf module for telemtry. Now i have to fix the issues of vias idk what to do here

Timelapse: https://lapse.hackclub.com/timelapse/fr6vyIiDoXoS

**Total time spent: 1h 18m**

# November 18, 2026: fixed DRC errors

I fixed up the drc errors by making a small trave connected to a via. Now i have to find a vway to draw a fillup for power(i think more power symbols ughhh as the nets have random names)

Timelapse: https://lapse.hackclub.com/timelapse/oHBjwVAlvzr_

**Total time spent: 30m**

# November 18, 2026: ok some more problems \ig

Ok so basically i found out that all my gnd pour / vias got reassigned to 5v so i panicked of c and did  cntrl z and i had to reassign gnd. I also made the switch jumper as one conn 1*2. Ive assigned the 5v, 3v3 and batt now. Now i have to make a fillup

Timelapse: https://lapse.hackclub.com/timelapse/CsSLd-o7LZg-

**Total time spent: 1h 18m**

# November 18, 2026: Almost done

I am almost done i spen nearly 1 hrs trying to fix a DRC warning with no luck and the board also is perfect for my goal of 8cm width.

Timelapse: https://lapse.hackclub.com/timelapse/ZKTOozMFpLNz

**Total time spent: 1h 24m**

# November 18, 2026: I was fixing the via errors

the issue wont go even affter i tried everything textbook asked for help nothing i thought it was clearence. Then i found out the probklem was that i forgot to mark b.cu in fillup ofc i was on the verge of crying.

Timelapse: https://lapse.hackclub.com/timelapse/B9vJaWN2kioX

**Total time spent: 4h 42m**

# November 19, 2026: I added the launch trigger started on code 

I forgot to add a launch trigger ofc so now i added a launch trigger such that if it goes high(pun intended) triggered by a devboard in ground station. I also added a nrf radio(cant say the full name) compatibillity in case ii want telemetry. I started to code as well along with me uploading the .stp of the TVC gimbal :)

Timelapse: https://lapse.hackclub.com/timelapse/QUfAHy5gDkzW

**Total time spent: 7h**

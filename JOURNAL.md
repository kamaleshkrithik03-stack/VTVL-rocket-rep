---
title: "My avionics bay for a vtvl rocket"
github: "https://github.com/kamaleshkrithik03-stack/VTVL-rocket-rep"
description: "This flight controller and sytem is made for my VTVL rocket(vertical takeoff vertical landing) which operates without an actual rocket engine!!"
created_at: "2026-10-21"
total_time: "7h 12m"
---

# October 24, 2026: I started with power diversion
<!-- fabricate:entry 1165 -->

in my experience- having the same powerline as the microcontroller and servos along with pyro channel in a rocket was a bit of a perfect condition for blackout of everything. the best solution i found was to add a cap to 2 different lines from same battery. One is the logic line consisting of my sensors and the black pill(last time it was an arduino nano but i find black pill superior) and another is purely for servos, pyro and the brushless motor.

Timelapse: https://lapse.hackclub.com/timelapse/t8QIn0WJG_cf

**Total time spent: 36m**

# October 27, 2026: I am done with logic power line
<!-- fabricate:entry 1323 -->

In the logic power line i added a lm2596 5v module which along with the 1000mhuf capacitor should keep the black pill and sensors away from a blackout. I've also added a pushbutton between the lm2596 and the black pill to keep the black pill safe from power spikes. Now i have to figure out a way to regulate servo power and brushless motor power.

Timelapse: https://lapse.hackclub.com/timelapse/_zzqxLqfELNa

**Total time spent: 12m**

# October 27, 2026 (entry 2): Done with the schematics(almost)
<!-- fabricate:entry 1331 -->

I am almost done with the schematics and am done with the connections. as you can see- i have replaced the ic lm2596 and xl4015 with a connector pin as i plan on physically placing a pre built version of them on the pcb as it is much easier than to have inductors and whatnot in the pcb in terms of space and replaceabillity(or redundancy). There are also 2 redundant slots in case i have future needs.

![](https://fabricate.hackclub-assets.com/5a56791c9a8460e8c859e8b53fef8bf4b711051bbc67b4966a34fef28a5a5adc/image-jpeg/j%2Chbsjk%2Cfjbf%2Cmxfbjkbjjbjjfb.JPG)

Timelapse: https://lapse.hackclub.com/timelapse/7C_BmZ6xk7Bf

**Total time spent: 1h**

# October 27, 2026 (entry 3): Finished with the schematics
<!-- fabricate:entry 1345 -->

I've replaced the power socket with a screw connecto because i thought that will be better for a VTVL rocket with so much vibrations. I've also added a status LED which can show the state of the rocket. The new pyro channel is for the future in case i decide to switch to a hobby engine instead of a brushless motor.

Timelapse: https://lapse.hackclub.com/timelapse/KaC37svzb_No

**Total time spent: 24m**

# November 17, 2026: assigning the footprints and research on motor
<!-- fabricate:entry 3275 -->

Ive been assigning footprints to the components keeping in mind that it has to handel a lot of current so i tried to take the biggest components(dont know how to phrase it) like 2.54 socket/headers. I also changed the esc power to a screw terminal as normally a esc has t connector but kicad doesnt have that component so next best was a terminal not a socket(what was i thinking). I also was researching on motors and thrust from 3s batteries and a good bldc/prop combo and changing it in the bom

Timelapse: https://lapse.hackclub.com/timelapse/w6HWBbpkSGLw

**Total time spent: 1h 30m**

# November 17, 2026 (entry 2): I did start with pcb ediitor
<!-- fabricate:entry 3287 -->

the pcb editor is so stressful like the nest is just confusing me now i have to start with the traces and im not sure if im doing it right.

Timelapse: https://lapse.hackclub.com/timelapse/nV1OmsoraC4K

**Total time spent: 1h**

# November 17, 2026 (entry 3): took out exact measurements for the pcb
<!-- fabricate:entry 3293 -->

I took out the exact measuremnts from google for d btw pins in the bucks and the black pill so i could try to make the pcb smaller.

Timelapse: https://lapse.hackclub.com/timelapse/dq6kU1n_zOBe

**Total time spent: 54m**

# November 17, 2026 (entry 4): added traces and more research
<!-- fabricate:entry 3301 -->

ive added traces and i cant just seem to find a way fro the last one ughhh. i dont know if i have to add another layer.

Timelapse: https://lapse.hackclub.com/timelapse/E-rpeMPYDdRp

**Total time spent: 1h 6m**

# November 17, 2026 (entry 5): Finished traces
<!-- fabricate:entry 3304 -->

ive finished the traces and also i gave some screw holes for mounting. It is withen my 8cm limit the pcb so im onk and also i added some labels. Now like debugging i have to do it in pcb.

![](https://fabricate.hackclub-assets.com/b3ad2fd9e29a5531917be4a69695d7af6c646d34b73d2ce1ba059da09db9c28c/image-jpeg/yayaya.JPG)

Timelapse: https://lapse.hackclub.com/timelapse/vk8ZdZCFb5v7

**Total time spent: 30m**

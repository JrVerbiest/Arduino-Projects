# MicroMod nRF52840 in platformIO

## Notes

Change the`platformio.ini` to

```
[env:nano33ble]
platform = nordicnrf52@7.1.0
board = nano33ble
framework = arduino
board_build.variant = SF_MM_nRF52840_PB
```

(` @7.1.0` is needed to get core version 1.3.2, bugfix of 1.3.1).

Rebuild your sketch. 

You **should** get errors now saying something like

> arm-none-eabi-g++: error: C:\Users\Max\.platformio\packages\framework-arduino-mbed@1.3.2\variants\SF_MM_nRF52840_PB\includes.txt: No such file or directory

Open the above path to the `variants` folder (so for above e.g. `C:\Users\Max\.platformio\packages\framework-arduino-mbed@1.3.2\variants\`). Download the variant definition [here](https://github.com/sparkfun/MicroMod_Processor_Board-nRF52840/archive/refs/heads/master.zip) and copy the `SF_MM_nRF52840_PB` from there into the `variants` folder. It should now look like

![grafik](https://community.platformio.org/uploads/default/original/2X/6/640f3d9836c20c9be123bb93bc04b5f22b37a4f5.png)

Then, rebuild the project. It should now give you a success.

```
RAM:   [==        ]  16.5% (used 43136 bytes from 262144 bytes)
Flash: [=         ]   7.8% (used 76604 bytes from 983040 bytes)
============== [SUCCESS] Took 13.93 seconds ==============
```
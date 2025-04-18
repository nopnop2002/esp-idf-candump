# esp-idf-candump
Example code for CAN receive using ESP-IDF.   

The ESP32 intregates a CAN controller which is compatible with the NXP SJA1000 CAN controller.   
Thus, it is CAN 2.0B specification compliant and supports two message formats:   
- Base frame format (11-bit ID)   
- Extended frame format (29-bit ID)   

ESP-IDF contains three example for TWAI, but you need two ESP32s running master and slave, or master and listen_only at the same time.   
So, I made a reception-only tool with Raspberry or Arduino as the sender.   

__Note for ESP-IDF V4.4 can bitrate__   
In ESP32 whose chip version is Rev2 or higher, the role of register bits related to CAN communication has been changed to mean "halve the communication speed".   
This is to support slower bitrates below 25Kbps.   
This fuature can be controlled by CONFIG_ESP32_REV_MIN.   
This fuature is enabled when CONFIG_ESP32_REV_MIN >= 2.   
See [here](https://www.esp32.com/viewtopic.php?t=15581) for detail.


# Software requirement    
ESP-IDF V4.4/V5.x.   
ESP-IDF V5.1 is required when using ESP32C6.   

# Hardware requirements

- SN65HVD23x CAN-BUS Transceiver   
SN65HVD23x series has 230/231/232.   
They differ in standby/sleep mode functionality.   
Other features are the same.   

- Termination resistance   
I used 150 ohms.   

# Wireing   
|SN65HVD23x||ESP32|ESP32-S2/S3|ESP32-C3/C6||
|:-:|:-:|:-:|:-:|:-:|:-:|
|D(CTX)|--|GPIO21|GPIO17|GPIO0|(*1)|
|GND|--|GND|GND|GND||
|Vcc|--|3.3V|3.3V|3.3V||
|R(CRX)|--|GPIO22|GPIO18|GPIO1|(*1)|
|Vref|--|N/C|N/C|N/C||
|CANL|--||||To CAN Bus|
|CANH|--||||To CAN Bus|
|RS|--|GND|GND|GND|(*2)|

(*1) You can change using menuconfig. But it may not work with other GPIOs.  

(*2) N/C for SN65HVD232


# Test Circuit   
```
   +-----------+   +-----------+   +-----------+ 
   | Atmega328 |   | Atmega328 |   |   ESP32   | 
   |           |   |           |   |           | 
   | Transmit  |   | Receive   |   | 21    22  | 
   +-----------+   +-----------+   +-----------+ 
     |       |       |       |       |       |   
   +-----------+   +-----------+     |       |   
   |           |   |           |     |       |   
   |  MCP2515  |   |  MCP2515  |     |       |   
   |           |   |           |     |       |   
   +-----------+   +-----------+     |       |   
     |       |       |       |       |       |   
   +-----------+   +-----------+   +-----------+ 
   |           |   |           |   | D       R | 
   |  MCP2551  |   |  MCP2551  |   |   VP230   | 
   | H      L  |   | H      L  |   | H       L | 
   +-----------+   +-----------+   +-----------+ 
     |       |       |       |       |       |   
     +--^^^--+       |       |       +--^^^--+
     |   R1  |       |       |       |   R2  |   
 |---+-------|-------+-------|-------+-------|---| BackBorn H
             |               |               |
             |               |               |
             |               |               |
 |-----------+---------------+---------------+---| BackBorn L

      +--^^^--+:Terminaror register
      R1:120 ohms
      R2:150 ohms(Not working at 120 ohms)
```

![ESP32-CAN-3V3](https://github.com/nopnop2002/esp-idf-candump/assets/6020549/dec3744e-ede1-41c7-99b6-77ebfe916123)

__NOTE__   
3V CAN Trasnceviers like VP230 are fully interoperable with 5V CAN trasnceviers like MCP2551.   
Check [here](http://www.ti.com/lit/an/slla337/slla337.pdf).



# Installation
```
git clone https://github.com/nopnop2002/esp-idf-candump
cd esp-idf-candump/stdout
idf.py set-target {esp32/esp32s2/esp32s3/esp32c3/esp32c6}
idf.py menuconfig
idf.py flash
```


# Configuration   
You have to set this config value with menuconfig.
- CAN Bitrate   
- CTX GPIO number   
- CRX GPIO number   

![config-top](https://github.com/nopnop2002/esp-idf-candump/assets/6020549/07bf1a64-e1a7-44c2-a0e5-b64d00d14e45)
![config-app-1](https://github.com/nopnop2002/esp-idf-candump/assets/6020549/98da3cce-dabd-4b6d-b833-8775b2af63ef)
![config-app-2](https://github.com/nopnop2002/esp-idf-candump/assets/6020549/635e41ec-f8b5-4024-b160-2714a9086f5f)

# ScreenShot   
![stdout](https://github.com/nopnop2002/esp-idf-candump/assets/6020549/bdad5960-b13f-497a-a3f5-a4bd749a1e3e)

# Acceptance Filter   
The explanation about the acceptance filter is available [here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/twai.html#acceptance-filter).   
There are diagrams of Bit layout of single filter mode and Bit layout of dual filter mode, but they are described in __Right side MSBit__.   
I've never seen a __Right side MSBit__ before, so I thought it was a Left side MSBit.   
I was very confused.   

# Reference   

https://github.com/nopnop2002/esp-idf-can2http

https://github.com/nopnop2002/esp-idf-can2mqtt

https://github.com/nopnop2002/esp-idf-can2usb

https://github.com/nopnop2002/esp-idf-can2websocket

https://github.com/nopnop2002/esp-idf-can2socket

https://github.com/nopnop2002/esp-idf-CANBus-Monitor

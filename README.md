# esp-idf-candump
Example code for CAN receive using ESP-IDF.   
ESP-IDF contains three example for TWAI, but you need two ESP32s running master and slave, or master and listen_only at the same time.   
So, I made a reception-only tool with Raspberry or Arduino as the sender.   

# Software requirement    
esp-idf v4.4/v5.0.   
Use twai(Two-Wire Automotive Interface) driver instead of can driver.   

# Hardware requirements
- SN65HVD23x CAN-BUS Transceiver   

- Termination resistance   
I used 150 ohms.   

# Wireing   
|SN65HVD23x||ESP32|ESP32-S2/S3|ESP32-C3||
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
     |       |      |        |       |       |   
   +-----------+   +-----------+     |       |   
   |           |   |           |     |       |   
   |  MCP2515  |   |  MCP2515  |     |       |   
   |           |   |           |     |       |   
   +-----------+   +-----------+     |       |   
     |      |        |      |        |       |   
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

__NOTE__   
3V CAN Trasnceviers like VP230 are fully interoperable with 5V CAN trasnceviers like MCP2551.   
Check [here](http://www.ti.com/lit/an/slla337/slla337.pdf).



# Installation
```
git clone https://github.com/nopnop2002/esp-idf-candump
cd esp-idf-candump
idf.py set-target {esp32/esp32s2/esp32s3/esp32c3}
idf.py menuconfig
idf.py flash
```


# Configuration   
You have to set this config value with menuconfig.
- CAN Bitrate   
- CTX GPIO number   
- CRX GPIO number   

![candump-1](https://user-images.githubusercontent.com/6020549/98186063-51caf680-1f51-11eb-8f42-85cabff71981.jpg)
![candump-2](https://user-images.githubusercontent.com/6020549/98186069-5394ba00-1f51-11eb-90f4-a4a46c7a5a66.jpg)
![candump-3](https://user-images.githubusercontent.com/6020549/98186076-57284100-1f51-11eb-98c7-faf8d70bd2ac.jpg)

![candump-4](https://user-images.githubusercontent.com/6020549/87237112-fff3e300-c42c-11ea-9a8c-1cf0cf0b755c.jpg)


# Acceptance Filter   
The explanation about the acceptance filter is available [here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/twai.html#acceptance-filter).   
There are diagrams of Bit layout of single filter mode and Bit layout of dual filter mode, but they are described in __Right side MSBit__.   
I've never seen a __Right side MSBit__ before, so I thought it was a Left side MSBit.   
I was very confused.   

# Reference   

https://github.com/nopnop2002/esp-idf-can2http

https://github.com/nopnop2002/esp-idf-can2mqtt

https://github.com/nopnop2002/esp-idf-can-browser

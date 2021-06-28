# esp-idf-candump
Example code for CAN receive using ESP-IDF.   

# Software requirement    
esp-idf v4.2-dev-2243 or later.   
Use twai(Two-Wire Automotive Interface) driver instead of can driver.   

# Hardware requirements
1. SN65HVD23x CAN-BUS Transceiver   

|SN65HVD23x||ESP32|ESP32-S2||
|:-:|:-:|:-:|:-:|:-:|
|D(CTX)|--|GPIO21|GPIO20|(*1)|
|GND|--|GND|GND||
|Vcc|--|3.3V|3.3V||
|R(CRX)|--|GPIO22|GPIO21|(*1)|
|Vref|--|N/C|N/C||
|CANL|--|||To CAN Bus|
|CANH|--|||To CAN Bus|
|RS|--|GND|GND|(*2)|

(*1) You can change using menuconfig.

(*2) N/C for SN65HVD232

2. Termination resistance   
I used 150 ohms.   

# Test Circuit   
```
   +-----------+ +-----------+ +-----------+ 
   | Atmega328 | | Atmega328 | |   ESP32   | 
   |           | |           | |           | 
   | Transmit  | | Receive   | | 32    33  | 
   +-----------+ +-----------+ +-----------+ 
     |       |    |        |     |       |   
   +-----------+ +-----------+   |       |   
   |           | |           |   |       |   
   |  MCP2515  | |  MCP2515  |   |       |   
   |           | |           |   |       |   
   +-----------+ +-----------+   |       |   
     |      |      |      |      |       |   
   +-----------+ +-----------+ +-----------+ 
   |           | |           | | D       R | 
   |  MCP2551  | |  MCP2551  | |   VP230   | 
   | H      L  | | H      L  | | H       L | 
   +-----------+ +-----------+ +-----------+ 
     |       |     |       |     |       |   
     +--^^^--+     |       |     +--^^^--+
     |   R1  |     |       |     |   R2  |   
 |---+-------|-----+-------|-----+-------|---| BackBorn H
             |             |             |
             |             |             |
             |             |             |
 |-----------+-------------+-------------+---| BackBorn L

      +--^^^--+:Terminaror register
      R1:120 ohms
      R2:150 ohms(Not working at 120 ohms)
```

__NOTE__   
3V CAN Trasnceviers like VP230 are fully interoperable with 5V CAN trasnceviers like MCP2551.   
Check [here](http://www.ti.com/lit/an/slla337/slla337.pdf).



# Installation for ESP32
```
git clone https://github.com/nopnop2002/esp-idf-candump
cd esp-idf-candump
idf.py set-target esp32
idf.py menuconfig
idf.py flash
```

# Installation for ESP32-S2
```
git clone https://github.com/nopnop2002/esp-idf-candump
cd esp-idf-candump
idf.py set-target esp32s2
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



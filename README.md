# esp-idf-candump
Example code for CAN receive using ESP-IDF.   

# Software requirement    
esp-idf v4.2-dev-2243 or later.   
Use twai(Two-Wire Automotive Interface) driver instead of can driver.   

# Hardware requirement    
3.3V CAN Bus Transceiver like SN65HVD230/231/232.   
Terminator register, If you have only 2 node.   

# Wirering for CAN Bus Transceiver   
|SN65HVD23x||ESP32||
|:-:|:-:|:-:|:-:|
|D(CTX)|--|GPIO21||
|GND|--|GND||
|Vcc|--|3.3V||
|R(CRX)|--|GPIO22||
|Vref|--|N/C||
|CANL|--||To CAN Bus|
|CANH|--||To CAN Bus|
|RS|--|GND(*1)||

(*1) N/C for SN65HVD232


# Test Circuit   
```
   +-----------+ +-----------+ +-----------+ 
   | Atmega328 | | Atmega328 | |   ESP32   | 
   |           | |           | |           | 
   | Transmit  | | Receive   | | 21    22  | 
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

# Install   
```
git clone https://github.com/nopnop2002/esp-idf-candump
cd esp-idf-candump
make menuconfig
make flash
```

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



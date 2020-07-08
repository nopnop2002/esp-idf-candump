# esp-idf-candump
Example code for CAN receive using ESP-IDF.   

# Hardware requirement    
3.3V CAN Bus Transceiver like SN65HVD230/231/232.   
Terminator register, If you have only 2 node.   

# Wirering for CAN Bus Transceiver   
|SN65HVD23x||ESP-32||
|:-:|:-:|:-:|:-:|
|D|--|GPIO21||
|GND|--|GND||
|Vcc|--|3.3V||
|R|--|GPIO22||
|Vref|--|N/C||
|CANL|--||To CAN Bus|
|CANH|--||To CAN Bus|
|RS|--|GND(*1)||

(*1) N/C for SN65HVD232


# Test Circuit   
```
   +----------+ +----------+ +----------+ 
   |Atmega328 | |Atmega328 | |   ESP32  | 
   |          | |          | |          | 
   | Transmit | | Receive  | | 21    22 | 
   +----------+ +----------+ +----------+ 
     |      |     |      |     |      |   
   +----------+ +----------+   |      |   
   |          | |          |   |      |   
   |  MCP2515 | |  MCP2515 |   |      |   
   |          | |          |   |      |   
   +----------+ +----------+   |      |   
     |      |     |      |     |      |   
   +----------+ +----------+ +----------+ 
   |          | |          | | D      R | 
   |  MCP2551 | |  MCP2551 | |  VP230   | 
   | H      L | | H      L | | H      L | 
   +----------+ +----------+ +----------+ 
     |      |     |      |     |      |   
     |      |     |      |     |      |----->STAB cable
     |      |     |      |     |      |   
 |-+-+------|-----+------|-----+------|-+-| BackBorn H
   >        |            |            | >
   >        |            |            | >
   >        |            |            | >
 |-+--------+------------+------------+-+-| BackBorn L

      +^^^+:Terminaror register

```

# Install   
```
git clone https://github.com/nopnop2002/esp-idf-candump
cd esp-idf-candump/
make menuconfig
make flash
```

# Adjust CAN Bitrate   
You have to adjust your CAN bitrate using menuconfig.   

![candump-1](https://user-images.githubusercontent.com/6020549/57606049-0b3a4d00-75a3-11e9-8efd-688ead135bb3.jpg)
![candump-2](https://user-images.githubusercontent.com/6020549/57606051-0b3a4d00-75a3-11e9-8bd3-4169e181a782.jpg)
![candump-3](https://user-images.githubusercontent.com/6020549/57606052-0bd2e380-75a3-11e9-99d4-9e2008c29fd4.jpg)

![candump-4](https://user-images.githubusercontent.com/6020549/57606053-0bd2e380-75a3-11e9-91ee-a52d892fcaff.jpg)


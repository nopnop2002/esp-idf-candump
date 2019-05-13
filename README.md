# esp-idf-candump
Example code for CAN receive using ESP-IDF.   

# Hardware requirement    
CAN Bus Transceiver like SN65HVD230/SN65HVD232.   
Terminator register, If you have only 2 node.   

# Wirering for CAN Bus Transceiver   
|Transceiver||ESP-32||
|:-:|:-:|:-:|:-:|
|VCC|--|3.3V||
|GND|--|GND||
|CTX|--|GPIO21||
|CRX|--|GPIO23||
|CANH|--||To CAN Bus|
|CANL|--||To CAN Bus|



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


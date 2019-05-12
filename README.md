# esp-idf-candump
Example code for CAN DUMP using ESP-IDF.   

# Hardware requirement    
CAN Bus Transceiver like SN65HVD230.   

# Wirering for CAN Bus Transceiver   
|Transceiver||ESP-32||
|:-:|:-:|:-:|:-:|
|VCC|--|3.3V||
|GND|--|GND||
|CTX|--|GPIO21||
|CRX|--|GPIO23||
|CANH|--||To CAN Bus|
|CANL|--||To Can Bus|



```
git clone https://github.com/nopnop2002/esp-idf-candump
cd esp-idf-candump/
make menuconfig
make flash
```

![config](https://user-images.githubusercontent.com/6020549/56449085-4f458380-6350-11e9-95f8-8583c3f78e80.jpg)


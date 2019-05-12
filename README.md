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
|CANL|--||To CAN Bus|



```
git clone https://github.com/nopnop2002/esp-idf-candump
cd esp-idf-candump/
make menuconfig
make flash
```

# Change Bit Rate   
You have to adjust your bit rate.   

```
static const can_timing_config_t t_config = CAN_TIMING_CONFIG_250KBITS();   
```


![esp-idf-candump](https://user-images.githubusercontent.com/6020549/57578347-6990fe00-74c5-11e9-9fb8-30569c723ab6.jpg)


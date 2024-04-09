# ble
Output received data to ble.   
You can use android/iOS.   

# Installation

```
git clone https://github.com/nopnop2002/esp-idf-candump
cd esp-idf-candump/ble
idf.py set-target {esp32/esp32s3/esp32c2/esp32c3/esp32c6}
idf.py menuconfig
idf.py flash
```

# Android Application   

- For ESP32, pair with ESP32_SPP_SERVER   

- For ESP32S3, pair with ESP32S3_SPP_SERVER   

- For ESP32C3, pair with ESP32C3_SPP_SERVER   

- For ESP32C6, pair with ESP32C6_SPP_SERVER   

- Launch the app and select device  
Menu->Devices->Bluetooth LE   

- Long press the device and select the Edit menu   
![ble-1](https://github.com/nopnop2002/esp-idf-uart2bt/assets/6020549/a7a6ced7-05ac-44b2-b809-905921939755)

- Select Custom and specify UUID   
![ble-2](https://user-images.githubusercontent.com/6020549/184459827-f62dc206-6bc2-41a7-9a88-74b9c84bbb89.JPG)

- Connect to device   
You can display CAN messages using Android.   
![ble-3](https://github.com/nopnop2002/esp-idf-candump/assets/6020549/a5a2c0ed-71de-46a5-8523-2a240a67b253)

# iOS Application   
[This](https://apps.apple.com/jp/app/bluetooth-v2-1-spp-setup/id6449416841) might work, but I don't have iOS so I don't know.   


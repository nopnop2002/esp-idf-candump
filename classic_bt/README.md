# classic_bt
Output received data to bluetooth.   
You can use android/iOS.   

![classic_bt](https://github.com/nopnop2002/esp-idf-candump/assets/6020549/e6c03df7-6f2a-4c38-b740-8b9cf708a0bb)

# Installation (ESP32 only)

```
git clone https://github.com/nopnop2002/esp-idf-mqtt2bt
cd esp-idf-mqtt2bt/classic_bt
idf.py set-target esp32
idf.py menuconfig
idf.py flash
```


# Android Application   
I used [this](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal) app.   

- Pair with ESP_SPP_ACCEPTOR   
 If you are asked to enter the Pin Code, the Pin Code is "1234".   

- Launch the app and select device  
Menu->Devices->Bluetooth Classic   
![classic-1](https://github.com/nopnop2002/esp-idf-mqtt2bt/assets/6020549/1dbef296-173e-4a49-afce-5db27bae3968)

- Connect to device   
You can display CAN messages using Android/iOS.   
![classic-2](https://github.com/nopnop2002/esp-idf-candump/assets/6020549/385efb1a-85d3-43da-a1ee-9d72cc3118a6)


# iOS Application   
[This](https://apps.apple.com/jp/app/bluetooth-v2-1-spp-setup/id6449416841) might work, but I don't have iOS so I don't know.   



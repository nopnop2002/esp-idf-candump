# simple sending
A simple data transmission example.   
This data is sent every second.   
```
Extended ID: 0x00000032  DLC: 8  Data: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07
Extended ID: 0x00000032  DLC: 8  Data: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07
Extended ID: 0x00000032  DLC: 8  Data: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07
Extended ID: 0x00000032  DLC: 8  Data: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07
```

# Test Circuit
```
   +-----------+   +-----------+
   |   ESP32   |   |   ESP32   |
   |  Receiver |   |  Sending  |
   | 21     22 |   | 21    22  |
   +-----------+   +-----------+
     |       |       |       |
   +-----------+   +-----------+
   | D       R |   | D       R |
   |   VP230   |   |   VP230   |
   | H       L |   | H       L |
   +-----------+   +-----------+
     |       |       |       |   
     +--^^^--+       +--^^^--+
     |   R1  |       |   R2  |   
 |---+-------|-------+-------|-------| BackBorn H
             |               |
             |               |
             |               |
 |-----------+---------------+-------| BackBorn L

      +--^^^--+:Terminaror register
      R1:120 ohms
      R2:120 ohms
```

If the transceiver and terminator are connected correctly, this will be displayed on the receiving side.   
![Image](https://github.com/user-attachments/assets/304c4d70-51c9-48cf-bb93-570315ae080b)

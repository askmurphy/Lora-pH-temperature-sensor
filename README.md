# LoRa pH temperature sensor

![image](img/sensor.jpg?raw=true "LoRa pH temperature sensor")

This is a nice LoRa sensor for measuring the pH and the temperature of your swimming pool, drainage-basin or whatever you like.

| Electronic design | LoRa T-Beam |
|------------|-------------|
| ![Electronic design](img/Schematic.png?raw=true "Electronic design") | ![T-Beam v1.1](img/T-BeamV1dot1.jpeg?raw=true "T-Beam v1.1") |


| cayenne.mydevices temperature graph | cayenne.mydevices pH graph|
|------------|-------------|
| ![Temperature graph](img/temperature.png?raw=true "Temperature graph") | ![pH graph](img/pH.png?raw=true "pH graph") |

# Parts

* [T-Beam v1.1](https://www.aliexpress.com/premium/Ttgo-T%25252dBeam-V1.1.html) 
* Kradex case: Z74JPH TM ABS
* Kradex case plate: https://www.thingiverse.com/thing:5322236

# Buttons
- The User button is fitted to the case, with this button you can enable/disable the LCD backlight.
- With the Calibrate mode button you can step through the usermenu: you can enable/disable GPS, and calibrate the pH-sensor with pH-buffers 4,7 and 10.
- The Calibrate button must be used to activate a specific usermenu option.

# Used software
- Visual Studio Code with PlatformIO
- LMIC node package: https://github.com/lnlp/LMIC-node

# LoRa setup
- you need to rename the lorawan-keys_example.h file into lorawan-keys.h and change the content, see LMIC documentation.
 
# Assembly-tips
- Desolder the T-Beam lIPO-holder, we don't use it: the pH-sensor drains the 18650 battery too fast.

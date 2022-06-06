# Insomnia-Arduino-union-GPS-and-Giroscope
![arduino nano](https://i2.wp.com/www.teachmemicro.com/wp-content/uploads/2019/06/Arduino-Nano-pinout.jpg?fit=1500%2C1500&ssl=1)
## GPS module which i use:
![GPS module](https://images.prom.ua/785520852_w500_h500_gsm-gprs-modul.jpg)
## The module I use to determine the accelerometer, magnetometer and gyroscope data:
![adafruit lsdsm1](https://cdn-learn.adafruit.com/guides/images/000/001/574/medium800/combo.jpg)
## Prototype view:
![Snapshot1](image_2022-06-06_15-55-46.png)
## Description
I connected an arduino nano module and adafruit lsdsm1 to the i2c protocol. At the moment, this is just a layout implemented on Bradboard, but I have already taken the following impressions from the sensors: 
+ Acceleration
+ Magnetic field strength (will not be used in the future)
+ Calculating the change in the angle of inclination relative to the axis when rotating the device.
+ Direction(compass)
+ Date and time
+ Distance to the Lviv Polytechnic National University
+ Speed in km per hour
+ Number of connected satellites
+ Longitude and latitude
+ Horizontal accuracy

In the future it is planned to connect GSM module and create a full-fledged prototype.

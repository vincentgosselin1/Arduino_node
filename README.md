

# This is the BELIOT project
This is an Internet Of Things project.
This project contains an Arduino Nano which is the core microcontroller of module.
The module contains an RF circuit (inAir9B) with LoRaWAN technology. This node sends
data to a Raspberry Pi via RF and the Raspberry Pi posts its data to a Webserver.
Webserver can be reach at beliotv3.herokuapp.com . Data is stored into InfluxDB and data
can be visualized with Grafana.

This unit monitores : 
- soil humidity/temperature
- air humidity/temperature
- Ozone concentration
- Dust concentration
- GPS
- Battery Life

Here is a picture of the Arduino node:
![beliot_pic](https://user-images.githubusercontent.com/16928726/29093577-4a29306c-7c58-11e7-8864-ddb7ac480732.png)

Here is the circuitry inside the Stevenson Cage:
![the_whole_thing](https://user-images.githubusercontent.com/16928726/29093455-e90f69e0-7c57-11e7-80f1-716bd4409998.JPG)

Here is the Raspberry Pi Gateway to receive/send data:
![rasp](https://user-images.githubusercontent.com/16928726/29094226-93257954-7c5a-11e7-94da-9a2da1cd18cb.JPG)

The PCBs and electronics circuits were made using the KiCad software.

A User Manual (in French) is to be found on PDF.

 

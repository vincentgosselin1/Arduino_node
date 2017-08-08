

# This is the BELIOT project
This is an Internet Of Things project.
This project contains an Arduino Nano which is the core microcontroller of module.
The module contains an RF circuit (inAir9B) with LoRaWAN technology. This node sends
data to a Raspberry Pi via RF and the Raspberry Pi posts its data to a Webserver via a Ruby script.
Webserver (Ruby on Rails app) can be reach at beliotv3.herokuapp.com . Data is stored into InfluxDB and data
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
![raspgithub](https://user-images.githubusercontent.com/16928726/29094369-166655cc-7c5b-11e7-8d36-807ad8b1e19a.png)

Here is a picture of successfull tranmission from Arduino node to Raspberry Pi (seen on rasp console):
![successfull_com](https://user-images.githubusercontent.com/16928726/29095162-f175a90e-7c5d-11e7-9ff5-2bbf4e1dd3f9.png)

Here is the landing page of the website:
![screen shot 2017-08-08 at 5 23 36 pm](https://user-images.githubusercontent.com/16928726/29095310-5f8bb9ce-7c5e-11e7-8f9c-d5be9c80da68.png)

Here is some data plotted using Grafana:
![some_data](https://user-images.githubusercontent.com/16928726/29095391-acc39662-7c5e-11e7-8b95-378279aaa10e.png)

The PCBs and electronics circuits were made using the KiCad software.

A User Manual (in French) is to be found on PDF.

 

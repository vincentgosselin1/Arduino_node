//Soil_moisture_v2.cpp by Vincent Gosselin, 2017.

//Custom library for https://www.dfrobot.com/product-1385.html
#include "arduino_soil_moisture.h"

soil_moisture soil_moisture(1);//Pin A1.

void setup() {
	Serial.begin(38400);
	Serial.println("Hello");
}

void loop() {
	delay(1000);
	soil_moisture.scan();
	delay(1000);
	Serial.print("Soil moisture is : ");Serial.println(soil_moisture.get_moisture(),DEC);
}
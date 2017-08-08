//Dust_sensor_v2.cpp by Vincent Gosselin, 2017.

//Custom library for Sharp Dust Sensor GP2Y1023AU0F
#include "sharp_dust_sensor.h"

sharp_dust_sensor sharp_dust_sensor(4);//Pin D4.

void setup() {
  // put your setup code here, to run once:
	Serial.begin(38400);
	Serial.println("Hello");
}

void loop() {
  // put your main code here, to run repeatedly:
	delay(500);
	sharp_dust_sensor.scan();
	delay(1000);
	Serial.print("Dust concentration is ");Serial.print(sharp_dust_sensor.get_concentration());Serial.println(" ugram/m^3");
}
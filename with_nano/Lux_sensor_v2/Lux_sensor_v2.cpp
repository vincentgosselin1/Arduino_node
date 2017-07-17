//Lux_sensor_v2.cpp, with reduced dynamic memory usage.

//DO NOT USE, actually worst in memory usage.
// Use, Lux_Sensor.h
#include "Lux_sensor_library_v2.h"

//SDA to A4, SCL to A5
LUX lux_sensor;

void setup(void) {
  Serial.begin(38400);
  Serial.println("Serial Begin");
}

void loop(void) {

  if(lux_sensor.scan())
    Serial.println(lux_sensor.get_lux());

 delay(500); 
 
 
}
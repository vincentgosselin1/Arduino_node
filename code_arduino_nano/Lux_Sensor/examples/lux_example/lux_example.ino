#include "Lux_Sensor.h"

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

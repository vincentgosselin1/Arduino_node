//Soil_temp_v2.cpp

//By Vincent Gosselin, 2017.
//with custom library

#include <arduino_nano_DFR0198.h>

DFR0198 DFR0198(3);//pin 3.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  Serial.println("Hello");
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  DFR0198.scan();
  Serial.print("Temperature is : ");Serial.print(DFR0198.get_temperature());Serial.println(" Degrees Celcius");
}
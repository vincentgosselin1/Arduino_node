#include <arduinonanodht22.h>

//MAIN

//arduino_nano_dht22_v2
//With custom library

//By Vincent Gosselin, 2017.

dht22 dht22(2);//PIN 2.


void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  Serial.println("Hello");

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  dht22.scan();
  delay(1000);

  //char lon_string[15];
  //dtostrf(lon,11, 6, lon_string);
  float air_humidity = dht22.get_humidity();
  float air_temperature = dht22.get_temperature();

  char air_humidity_string[15] = {0};
  dtostrf(air_humidity,5, 1, air_humidity_string);

  char air_temperature_string[15] = {0};
  dtostrf(air_temperature,5, 1, air_temperature_string);


  Serial.print("Humidity is : ");Serial.println(air_humidity_string);
  Serial.print("Temperature is : ");Serial.println(air_temperature_string);
}
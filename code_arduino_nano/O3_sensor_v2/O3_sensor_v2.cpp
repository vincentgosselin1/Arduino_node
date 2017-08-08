//O3_sensor_v2.pp by Vincent Gosselin, 2017.

#include "O3_spec_sensor.h"

O3_spec_sensor O3_spec_sensor(0); //A0;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(38400);
	Serial.println("hello");
}

void loop() {
	// put your main code here, to run repeatedly:
	delay(1000);
	O3_spec_sensor.scan();
	Serial.print("O3 concentration is ");Serial.print(O3_spec_sensor.get_concentration());Serial.println(" ppb");

}

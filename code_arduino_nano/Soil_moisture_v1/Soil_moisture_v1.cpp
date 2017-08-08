//Soil_moisture_v1.cpp

int analogPin1 = 1;

void setup() {
// put your setup code here, to run once:
	Serial.begin(38400);
	Serial.println("Hello");
}

void loop() {
// put your main code here, to run repeatedly:
	delay(1000);
	int adc_value = analogRead(analogPin1);
	//Serial.println(adc_value);

	//Formula to convert ADC value to moisture (Relative Humidity (RH%)). 
	//Sensor calibrated at 34% in AIR, 100% in WATER. Theoretical 0% at 702 adc value.
	unsigned int moisture = ((unsigned int)(702-adc_value)*100)/432.0;
	Serial.println(moisture);

}
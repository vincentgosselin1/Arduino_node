//Dust_sensor_v1.cpp by Vincent Gosselin, 2017.

//Lots of tweak here to get the right value.

//DigitalPin 4 used for dust sensor
int digitalpin4 = 4;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(38400);
	Serial.println("Hello");


	pinMode(digitalpin4, INPUT);
}

void loop() {
	// put your main code here, to run repeatedly:
	
	//At startup, VO is high for 1 sec.
	delay(1000);
	//Pre-counting. Signal is high.
	while(digitalRead(digitalpin4)!=0);
	while(digitalRead(digitalpin4)!=0);

	//Counting the milliseconds. Signal is low.
	// j keeps track of time elapsed during signal is low.
	// Calibrated with pulse low for 1.457ms.
	int j = 0;
	while(digitalRead(digitalpin4)==0){
		j++;
	}
	
	//Counting is done. Signal is high.
	while(digitalRead(digitalpin4)!=0);

	//What is j on average? average is 353.63 and corresponds to 1.457ms.	
	//Serial.print(j);Serial.print(" ");

	float factor1 = 242.71;//To be adjusted for the lib since memory access are slower.
	float calculated_ms = ((float)j)/factor1;
	//Serial.print(calculated_ms);Serial.print(" ");

	float factor2 = 1.1534;//Needed since didn't get 1.457 with first factor.
	calculated_ms = calculated_ms * factor2;
	//Serial.print(calculated_ms);Serial.print(" ");

	//Trying to get it...
	//Still didn't get to 1.457, got 1.324 on average. add the 0.133 offset
	float offset = 2*0.133 + 0.095;//Close enough 1.4892
	calculated_ms = calculated_ms + offset;
	//Serial.print(calculated_ms);Serial.print(" ");


	//Now convert to Analog voltage value
	//Formulae :  AD_value = (x/7) * 5000 mV
	float AD_value = (calculated_ms/7.0)*5000.0;
	//Serial.print(AD_value);Serial.print(" ");

	//Still need to tweek, for 1.457ms I found AD_value = 1041...
	//1050.3 not bad for the average. CANNOT GO UNDER 1000.
	if(AD_value < 1000.0){
		AD_value = 1000.0;
	}

	//Now converting AD_value to micro gram / m^3 for dust weight/volume.
	float dust = (AD_value - 1000.0)*0.075;
	Serial.print(dust);Serial.print(" ");

	//Close enough, first result is 29.37ug/m^3 and reference is 30.75ug/m^3.


}






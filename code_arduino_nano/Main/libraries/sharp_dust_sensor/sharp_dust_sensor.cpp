//sharp_dust_sensor.cpp library by Vincent Gosselin, 2017.
#include "sharp_dust_sensor.h"

//Following code is for Sharp Dust Sensor GP2Y1023AU0F
sharp_dust_sensor::sharp_dust_sensor(int pin)
{
	_pin=pin;
	_concentration = 0;

	//Sharp dust sensor output is a PWM.
	pinMode(_pin, INPUT);
}

void sharp_dust_sensor::scan(void){

	//calibrated with signal LOW lasting 1.491ms. AD_value should be 1065.

	//Pre-counting. Signal is high.
	while(digitalRead(_pin)!=0);
	while(digitalRead(_pin)!=0);

	//Counting the milliseconds. Signal is low.
	// j keeps track of time elapsed during signal is low.
	// Calibrated with pulse low for 1.491ms.
	int j = 0;
	while(digitalRead(_pin)==0){
		j++;
	}
	
	//Counting is done. Signal is high.
	while(digitalRead(_pin)!=0);

	//What is j on average? average is 283.18 and corresponds to 1.491ms.	
	//Serial.print(j);Serial.print(" ");

	float factor1 = 189.926;//To be adjusted for the lib since memory access are slower.
	float calculated_ms = ((float)j)/factor1;
	//Serial.print(calculated_ms);Serial.print(" ");

	float factor2 = 1.155;//Needed since didn't get 1.491 with first factor. Got 1.155 instead.
	calculated_ms = calculated_ms * factor2;
	//Serial.print(calculated_ms);Serial.print(" ");

	//Trying to get it...
	//Still didn't get to 1.491, got 1.461 on average. 1.5084 good enough.
	float offset = 0.194; 
	calculated_ms = calculated_ms + offset;
	//Serial.print(calculated_ms);Serial.print(" ");


	//Now convert to Analog voltage value.
	//Formulae :  AD_value = (x/7) * 5000 mV
	//Still need to tweek, for 1.491ms expecting AD_value = 1065, at first found 966.19.
	float AD_value = (calculated_ms/7.0)*5000.0*1.102*1.059;
	//Serial.print(AD_value);Serial.print(" ");


	//1068.3 not bad for the average. CANNOT GO UNDER 1000.
	if(AD_value < 1000.0){
		AD_value = 1000.0;
	}

	//Now converting AD_value to micro gram / m^3 for dust weight/volume.
	//Expecting 48.75ugram/m^3. Need some tweeking again uhh..
	// 46.50 ugram/m^3
	float dust = (AD_value*1.10 - 1000.0)*0.075*6.200;

	//Taking out first out of range result.
	if(dust > 100.0){
		dust = dust/10.0;
	}

	// //Seems good now.
	_concentration = dust;
}

float sharp_dust_sensor::get_concentration(void){
	return _concentration;
}
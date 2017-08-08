//Lib
#include "arduino_soil_moisture.h"

soil_moisture::soil_moisture(int pin)
{
	_pin=pin;
	_moisture = 0;
}

void soil_moisture::scan()
{
	int adc_value = analogRead(_pin);
	_moisture = ((unsigned int)(702-adc_value)*100)/432.0;
}

int soil_moisture::get_moisture()
{
	return _moisture;
}

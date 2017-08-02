//Library
//arduinonanodht22.h

#define arduinonanodht22_h

#include "Arduino.h"

class dht22
{
	public:
		dht22(int pin);
		void scan();
		float get_temperature();
		float get_humidity();

	private:
		int _pin;
		int _integral_RH;
		int _decimal_RH;//Used in DHT22
		int _integral_T;
		int _decimal_T;//Used in DHT22
		float _temperature;
		float _humidity;
};
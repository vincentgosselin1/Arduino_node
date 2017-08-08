//Library
//arduinonanodht11.h

#define arduinonanodht11_h

#include "Arduino.h"

class dht11
{
	public:
		dht11(int pin);
		void scan();
		int get_temperature();
		int get_humidity();

	private:
		int _pin;
		int _integral_RH;
		int _decimal_RH;//Not used in DHT11
		int _integral_T;
		int _decimal_T;//Not used in DHT11
};
//Library
//arduino_soil_moisture.h

#define arduino_soil_moisture_h

#include "Arduino.h"

class soil_moisture
{
	public:
		soil_moisture(int pin);
		void scan();
		int get_moisture();

	private:
		int _pin;
		int _moisture;
};
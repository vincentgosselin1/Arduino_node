//sharp_dust_sensor.h library
#define sharp_dust_sensor_h

#include "Arduino.h"

class sharp_dust_sensor
{
	public:
		sharp_dust_sensor(int pin);
		void scan();
		float get_concentration();

	private:
		int _pin;
		float _concentration;
};
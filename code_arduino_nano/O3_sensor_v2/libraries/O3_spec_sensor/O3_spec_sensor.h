//O3_spec_sensor.h Library
#define O3_spec_sensor_h

#include "Arduino.h"

class O3_spec_sensor
{
	public:
		O3_spec_sensor(int pin);
		void scan();
		float get_concentration();

	private:
		int _pin;
		float _concentration;//En PPB!
};
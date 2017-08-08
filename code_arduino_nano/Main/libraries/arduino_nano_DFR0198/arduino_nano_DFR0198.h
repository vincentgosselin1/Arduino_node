//arduino_nano_DFR0198.h library

#define arduino_nano_DFR0198_h

#include <OneWire.h>

class DFR0198
{
	public:
		DFR0198(int pin);
		void scan();
		float get_temperature();

	private:
		int _pin;
		float _TemperatureSum;
};

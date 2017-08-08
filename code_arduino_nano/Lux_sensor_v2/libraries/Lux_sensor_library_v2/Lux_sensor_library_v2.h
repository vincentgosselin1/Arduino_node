
#define Lux_sensor_v2_library_h

#include "Arduino.h"
#include <Wire.h>

//FROM https://github.com/adafruit/TSL2561-Arduino-Library
#include "TSL2561_v2.h"

class LUX{

	public:
		LUX();
		int scan();
		uint32_t get_lux();


	private:
	
			
		uint32_t lum, lux ;
		uint16_t ir, full;
		int sensor_found;
		TSL2561 *_tsl;
	
	};





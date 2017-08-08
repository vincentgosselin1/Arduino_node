
#ifndef LUX_h
#define LUX_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

//FROM https://github.com/adafruit/TSL2561-Arduino-Library
#include "TSL2561.h"

class LUX{

	public:
		LUX();
		int scan();
		uint32_t get_lux();


	private:
	
			
		uint32_t lum, lux ;
		uint16_t ir, full;
		int sensor_found;
		TSL2561 tsl;
	
	};

#endif



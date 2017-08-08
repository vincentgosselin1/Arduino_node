
#ifndef GPS_h
#define GPS_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SoftwareSerial.h>
#include <TinyGPS.h>

class GPS{

	public:
		GPS(int RX, int TX);
		int scan();
		float get_lat();
		float get_lon();


	private:
	
		float lat;
		float lon;
		int new_data;
		unsigned long age;

		int _TX;
		int _RX;
		
		SoftwareSerial ss;
		TinyGPS gps;
	
	};

#endif



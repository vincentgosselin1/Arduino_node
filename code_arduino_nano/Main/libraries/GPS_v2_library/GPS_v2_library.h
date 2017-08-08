//GPS_v2_library.h library.

#define GPS_v2_library_h

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <TinyGPS_v2.h>

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
		
		SoftwareSerial *_ss;
		TinyGPS *_gps;
	
	};




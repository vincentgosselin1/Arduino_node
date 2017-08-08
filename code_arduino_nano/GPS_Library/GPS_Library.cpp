#include "GPS_Library.h"



GPS::GPS(int RX, int TX) : ss(SoftwareSerial(RX, TX)){

	_TX = TX;
	_RX = RX;

	//ss.begin(9600);
	
	TinyGPS gps;
	
	lat = 0;
	lon = 0;
	new_data = 0;
	age = 0;

}


int GPS::scan(){
	
	// For one second we parse GPS data and report some key values

	//init software serial
	ss.begin(9600);

	new_data =0;
	
	for (unsigned long start = millis(); millis() - start < 1000;)
	{
		while (ss.available())
		{
			char c = ss.read();
			if (gps.encode(c)) // Did a new valid sentence come in?
				new_data = 1;
			
		}
	}
	
	gps.f_get_position(&lat, &lon, &age);

	//close Software Serial
	ss.end();

	return new_data;
}


float GPS::get_lat(){
	
	return lat;
}

float GPS::get_lon(){
	
	return lon;
}
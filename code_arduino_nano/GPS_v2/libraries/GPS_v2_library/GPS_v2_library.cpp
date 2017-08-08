#include "GPS_v2_library.h"

GPS::GPS(int RX, int TX){

	_TX = TX;
	_RX = RX;

	//_pin = new Digital_pin(pin);//Creating object Digital_pin.
	_ss = new SoftwareSerial(RX, TX);

	//_ss->begin(9600);
	
	_gps = new TinyGPS();
	//TinyGPS gps;
	
	lat = 0;
	lon = 0;
	new_data = 0;
	age = 0;

}


int GPS::scan(){
	
	// For one second we parse GPS data and report some key values

	//Init Software Serial
	_ss->begin(9600);
	
	new_data =0;
	
	for (unsigned long start = millis(); millis() - start < 1000;)
	{
		while (_ss->available())
		{
			char c = _ss->read();
			if (_gps->encode(c)) // Did a new valid sentence come in?
				new_data = 1;
			
		}
	}
	
	_gps->f_get_position(&lat, &lon, &age);

	//close Software Serial
	_ss->end();

	return new_data;
}


float GPS::get_lat(){
	
	return lat;
}

float GPS::get_lon(){
	
	return lon;
}
#include "Lux_sensor_library_v2.h"



LUX::LUX(){

	//_ss = new SoftwareSerial(RX, TX);
	_tsl = new TSL2561(TSL2561_ADDR_FLOAT);

	lum = 0;
	lux = 0;
	ir = 0;
	full = 0;
	sensor_found = 0;
	
}


int LUX::scan(){
	
	
	if (sensor_found == 0){
		if (_tsl->begin()){
			
			sensor_found = 1;
			
			//Change Gain and Timing depending on the situation
			//tsl.setGain(TSL2561_GAIN_16X); 
			_tsl->setGain(TSL2561_GAIN_0X); 
			_tsl->setTiming(TSL2561_INTEGRATIONTIME_101MS);

		}
	}
	
	lum = _tsl->getFullLuminosity();
	ir = lum >> 16;
	full = lum & 0xFFFF;
	
	lux = _tsl->calculateLux(full, ir);
	
	return sensor_found;
}


 uint32_t LUX::get_lux(){
	
	return lux;
}

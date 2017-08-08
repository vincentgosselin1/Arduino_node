#include "Lux_Sensor.h"



LUX::LUX() : tsl(TSL2561(TSL2561_ADDR_FLOAT)){

		
	lum = 0;
	lux = 0;
	ir = 0;
	full = 0;
	sensor_found = 0;
	
}


int LUX::scan(){
	
	
	if (sensor_found == 0){
		if (tsl.begin()){
			
			sensor_found = 1;
			
			//Change Gain and Timing depending on the situation
			//tsl.setGain(TSL2561_GAIN_16X); 
			tsl.setGain(TSL2561_GAIN_0X); 
			tsl.setTiming(TSL2561_INTEGRATIONTIME_101MS);

		}
	}
	
	lum = tsl.getFullLuminosity();
	ir = lum >> 16;
	full = lum & 0xFFFF;
	
	lux = tsl.calculateLux(full, ir);
	
	return sensor_found;
}


 uint32_t LUX::get_lux(){
	
	return lux;
}

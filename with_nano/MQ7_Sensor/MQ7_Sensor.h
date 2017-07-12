
#ifndef MQ7_h
#define MQ7_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class MQ7{

	public:
		MQ7(int PWM_pin, int reading_pin);
		int get_preheat_state();
		int scan();
		int get_CO_concentration();


	private:
		unsigned long time;
		unsigned long prev_time;
		unsigned long state_time;
		
		int CO_value;
		int state;
		int reading;

		int _PWM_pin;
		int _reading_pin;
	
	};

#endif



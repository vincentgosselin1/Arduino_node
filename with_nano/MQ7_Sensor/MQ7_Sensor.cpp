#include "MQ7_Sensor.h"


MQ7::MQ7(int PWM_pin, int reading_pin){

	pinMode(PWM_pin, OUTPUT);
	//pinMode(reading_pin, INPUT);, not required.
	
	_PWM_pin = PWM_pin;
	_reading_pin = reading_pin;

	

	state = 0;
	CO_value = 0;
	time = millis();
	prev_time = time;
  	state_time = 0; 

}

int MQ7::get_preheat_state(){
  
  time = millis();
  
  // see if enough time has passed to change state
  if ( (time - prev_time) > (state_time * 1000) ){
    prev_time = time;
    state_time = 0;


    switch(state) {

      // start heating
      case 0:
        state = 1;
        state_time = 60;  // 60 seconds at 5v
        digitalWrite(_PWM_pin, HIGH);
        break;
  
      // start cooling
      case 1:
        state = 2;
        state_time = 90;  //90 seconds at 1.4v
        analogWrite(_PWM_pin, 71); // need to use analogWrite to digital PWM pin
        break;
  
      // cooling is finished
      case 2:
        state = 3;
        break;
  
      default:
        // indefinite state until the value is read
        break;
    }
  }
  
  return state;
}

int MQ7::scan(){
	digitalWrite(_PWM_pin, HIGH);
	reading = analogRead(_reading_pin);
	analogWrite(_PWM_pin, 71);
	
	if (reading > 0)
		return 1;
	else
		return 0;

}


int MQ7::get_CO_concentration(){
	
	CO_value = reading;
	return CO_value;
}
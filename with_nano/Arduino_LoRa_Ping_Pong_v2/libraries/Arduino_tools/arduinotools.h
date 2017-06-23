//Custom arduino tools.
//By Vincent Gosselin, 2017.


/*
SmartWait is a class used to trigger events that happens once 
in a while without interupting the whole program. The wait function 
returns 1 when the time in ms has passed.

//How to USE

#include "arduinotools.h"

SmartWait timer1;
int j = 0 ;
Serial.begin(9600);


if(timer1.wait(1000)) {
	Serial.print("Counting j = "); Serial.println(j); j++;
}
*/

class SmartWait
{
	public:
		SmartWait();
		bool wait(int ms);//in milliseconds (0.001 Second). When timer is done, exits with being TRUE.
	private:
		unsigned long _previousMillis;
};

SmartWait::SmartWait()
{
	_previousMillis=0;//0 a start;
}

bool SmartWait::wait(int ms)
{
	//Get current time.
	unsigned long currentMillis = millis();
		//Condition to break overflow that happens after 50days when previousmillis is greater than currentmillis.
		if(_previousMillis > currentMillis)
		{
			_previousMillis = 0;
			return 0;
		}
		//If diffence is greater then ms.
		if(currentMillis - _previousMillis >= ms) {
 			_previousMillis = currentMillis;
 			//Time in ms is now done.
 			return 1;            
		} 
		else {
			//Time in ms did not passed.
			return 0;
		}
}
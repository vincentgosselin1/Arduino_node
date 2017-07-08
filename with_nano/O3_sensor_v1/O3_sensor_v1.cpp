//O3_sensor_v1 by Vincent Gosselin, 2017.
//SPEC Sensors, ULPSM-03.

//Formulae for Ozone concentration in the air (in ppm, Particles par Million)
/*
	Cx = (1/M)*(Vgas-Vgas0)

	where M = Sensivity_code * TIA_Gain * 10^-9 * 10^3

	where Sensivity code is 15.96nA/ppm (This is on the label of the sensor)

	where TIA_Gain is 499KV/A (this is also on the label of the sensor)

	where Vgas is a voltage on pin 1 from 0-3V.

	where Vgas0 is the reference for 0ppm of Ozone in air. 

	The Cx needs to be compensated in temperature.
	Linear approximations of the datasheet are used. 
	Temperature coefficient of Span (%/oC) 
		-> -20oC to 20oC  = -0.33%/oC
		-> 20oC to 40oC = 0.26%/oC
	Temperature coefficient of Zero Shift (ppm/oC)
		-> -20oC to 0oC = 0ppm/oC
		->  0oC to 25oC = 0.002ppm/oC
		-> 25oC to 40oC = -0.002ppm/oC

*/

//From sensor label.		
//#define SENSITIVITY_CODE 15.96
//#define TIA_GAIN 499

//Calculation of M
//#define M SENSITIVITY_CODE*TIA_GAIN*1000/1000000000		
#define ONE_DIVIDED_BY_M 125.57 //M is originally 0.007964. 

//Pin A0 is used by O3_sensor
//Analog pin is 10bit definition. Range is 0-1023.
int analogPin0 = 0;
int analogPin1 = 1;

//Vgas is voltage on pin A0.
double vgas = 0;

//Vref is voltage on pin A1.
double vref = 0;

//Vgas0 is 3.3V/2 = 1.65V by default. Solve(X/1023 = 1.65V/5V), X = 338 is baseline.
//In datasheet of sensor, Vgas0 = 0 when temp is 20oC.
#define VGAS0_VOLTAGE 1.65
int temperature = 20;


void setup() {
  // put your setup code here, to run once:
	//Serial.begin(38400);
}

void loop() {

	delay(100);

	//double vgas_total = 0;
	//double vref_total = 0;
	// for(int i = 0; i < 500; i++){
	// 	vgas_total += analogRead(analogPin0);
	// 	//vref_total += analogRead(analogPin1);
	// 	//delay(1);
	// }

	//vgas = vgas_total/500.0;
	//vref = vref_total/500.0;

	//Serial.println(vgas);
	//Serial.println(vref);

    // put your main code here, to run repeatedly:
	//vgas = analogRead(analogPin0);
	// double vgas_voltage = (double)vgas*5/1023;
	// double delta_vgas = vgas_voltage-VGAS0_VOLTAGE;
	// if(delta_vgas<0){
	// 	//should not be under 0.
	// 	delta_vgas = 0;
	// }
	// //Calculations for Cx (concentration in PPM)
	// double Cx;
	// //Pre-temperature compensated
	// Cx = (double)(ONE_DIVIDED_BY_M)*(delta_vgas);

	//Serial.println(vgas);
	//Serial.println(delta_vgas);
	//Serial.println(Cx);
	//Serial.println("ppm concentration is %d",Cx);
}





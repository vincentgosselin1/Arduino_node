//arduino_nano_DFR0198.cpp library
#include "arduino_nano_DFR0198.h"

//Inspired by https://www.dfrobot.com/wiki/index.php/Waterproof_DS18B20_Digital_Temperature_Sensor_(SKU:DFR0198)

DFR0198::DFR0198(int pin)
{
	//This pin should be pulled high by a resistor.
	_pin=pin;
	_TemperatureSum = 0;
}

float DFR0198::get_temperature(void){
	return _TemperatureSum;
}

void DFR0198::scan()
{
	//scan the temperature from one DS18S20 in DEG Celsius
	//Temperature chip i/o
	OneWire ds(_pin);

	byte data[12];
	byte addr[8];

	if ( !ds.search(addr)) {
	  //no more sensors on chain, reset search
	  ds.reset_search();
	  //return -1000;
	}

	if ( OneWire::crc8( addr, 7) != addr[7]) {
	  Serial.println("CRC is not valid!");
	  //return -1000;
	}

	if ( addr[0] != 0x10 && addr[0] != 0x28) {
	  Serial.print("Device is not recognized");
	  //return -1000;
	}

	ds.reset();
	ds.select(addr);
	ds.write(0x44,1); // start conversion, with parasite power on at the end

	byte present = ds.reset();
	ds.select(addr);    
	ds.write(0xBE); // Read Scratchpad


	for (int i = 0; i < 9; i++) { // we need 9 bytes
	data[i] = ds.read();
	}

	ds.reset_search();

	byte MSB = data[1];
	byte LSB = data[0];

	float tempRead = ((MSB << 8) | LSB); //using two's compliment
	_TemperatureSum = tempRead / 16;

}

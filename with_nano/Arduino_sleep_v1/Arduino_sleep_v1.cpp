// **** INCLUDES *****
#include "LowPower.h"

void setup()
{
  // No setup is required for this library
	//Serial.begin(38400);
  //Serial.begin(38400);
}

void loop() 
{
  // Enter idle state for 8 s with the rest of peripherals turned off
  // Each microcontroller comes with different number of peripherals
  // Comment off line of code where necessary

  // ATmega328P, ATmega168

  //IDLE
  // LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
  //               SPI_OFF, USART0_OFF, TWI_OFF);

  //PowerDown
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 

  Serial.begin(38400);
  delay(1000);
  
  Serial.println("hello there!");
  delay(1000);

  // int i  = 0;
  // pinMode(13,OUTPUT);  

  // //Flash LED 10 times
  // while(i<10){
  //   digitalWrite(13,0);  
  //   delay(200);
  //   digitalWrite(13,1);  
  //   delay(200);
  //   i++;
  // }

  // digitalWrite(13,0);  

  // ATmega32U4
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF, 
  //		  TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_OFF);

  // ATmega2560
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER5_OFF, TIMER4_OFF, TIMER3_OFF, 
  //		  TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART3_OFF, 
  //		  USART2_OFF, USART1_OFF, USART0_OFF, TWI_OFF);

  // ATmega256RFR2
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER5_OFF, TIMER4_OFF, TIMER3_OFF, 
  //      TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF,
  //      USART1_OFF, USART0_OFF, TWI_OFF);

  // Do something here
  // Example: Read sensor, data logging, data transmission.
}
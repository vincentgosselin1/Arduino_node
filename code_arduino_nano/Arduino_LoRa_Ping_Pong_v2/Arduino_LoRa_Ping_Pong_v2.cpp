//Arduino_LoRa_Ping_Pong V2.
//By Vincent Gosselin.

//This is using a nice library to simplify the code.
#include "Lora_simplified.h"
//Custom tools for a better code.
#include "arduinotools.h"

//Testing the sending of values  
int i = 0;

//SmarWait timer, from arduinotools lib.
SmartWait timer1;

void setup()
{
  Lora_init();
}


void loop(void)
{
  //Constructing a string with a new value of i everytime.
  i++;

  //wait 5 seconds
  if(timer1.wait(5000)) 
  {
    //string to send
    char string[100];
    sprintf(string, "\\!Value of i is : %d", i);
    Lora_send_string(string);
  }          
}


















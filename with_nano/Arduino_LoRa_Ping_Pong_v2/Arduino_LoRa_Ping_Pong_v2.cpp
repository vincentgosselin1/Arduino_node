//Arduino_LoRa_Ping_Pong V2.
//By Vincent Gosselin.

//This is using a nice library to simplify the code.

#include "Lora_simplified.h"

void setup()
{
  int e;
  
  // Open serial communications and wait for port to open:
#if defined __SAMD21G18A__ && not defined ARDUINO_SAMD_FEATHER_M0 
  SerialUSB.begin(38400);
#else
  Serial.begin(38400);  
#endif 

  // Print a start message
  PRINT_CSTSTR("%s","Simple LoRa ping-pong with the gateway\n");  

#ifdef ARDUINO_AVR_PRO
  PRINT_CSTSTR("%s","Arduino Pro Mini detected\n");
#endif

#ifdef ARDUINO_AVR_NANO
  PRINT_CSTSTR("%s","Arduino Nano detected\n");
#endif

#ifdef ARDUINO_AVR_MINI
  PRINT_CSTSTR("%s","Arduino MINI/Nexus detected\n");
#endif

#ifdef __MK20DX256__
  PRINT_CSTSTR("%s","Teensy31/32 detected\n");
#endif

#ifdef __SAMD21G18A__ 
  PRINT_CSTSTR("%s","Arduino M0/Zero detected\n");
#endif

  // Power ON the module
  sx1272.ON();
  
  // Set transmission mode and print the result
  e = sx1272.setMode(loraMode);
  PRINT_CSTSTR("%s","Setting Mode: state ");
  PRINT_VALUE("%d", e);
  PRINTLN;

  // enable carrier sense
  sx1272._enableCarrierSense=true;
    
  // Select frequency channel
  e = sx1272.setChannel(DEFAULT_CHANNEL);
  PRINT_CSTSTR("%s","Setting Channel: state ");
  PRINT_VALUE("%d", e);
  PRINTLN;
  
  // Select amplifier line; PABOOST or RFO
#ifdef PABOOST
  sx1272._needPABOOST=true;
  // previous way for setting output power
  // powerLevel='x';
#else
  // previous way for setting output power
  // powerLevel='M';  
#endif

  // previous way for setting output power
  // e = sx1272.setPower(powerLevel); 

  e = sx1272.setPowerDBM((uint8_t)MAX_DBM); 
  PRINT_CSTSTR("%s","Setting Power: state ");
  PRINT_VALUE("%d", e);
  PRINTLN;
  
  // Set the node address and print the result
  e = sx1272.setNodeAddress(node_addr);
  PRINT_CSTSTR("%s","Setting node addr: state ");
  PRINT_VALUE("%d", e);
  PRINTLN;
  
  // Print a success message
  PRINT_CSTSTR("%s","SX1272 successfully configured\n");

  delay(500);
}


void loop(void)
{
  uint8_t r_size;
  int e;

  sx1272.CarrierSense();

  sx1272.setPacketType(PKT_TYPE_DATA);

  //r_size=sprintf((char*)message, "This is a test");
  //Testing the sending of values  
  int i = 0;

  while (1) {

      //Constructing a string with a new value of i everytime.
      i++;
      r_size=sprintf((char*)message, "\\!Value of i is : %d", i);

      PRINT_CSTSTR("%s","Sending Ping");  
      PRINTLN;
            
      e = sx1272.sendPacketTimeoutACK(DEFAULT_DEST_ADDR, message, r_size);

      // this is the no-ack version
      // e = sx1272.sendPacketTimeout(DEFAULT_DEST_ADDR, message, r_size);
            
      PRINT_CSTSTR("%s","Packet sent, state ");
      PRINT_VALUE("%d", e);
      PRINTLN;
      
      if (e==3)
          PRINT_CSTSTR("%s","No Pong!");
        
      if (e==0)
          PRINT_CSTSTR("%s","Pong received from gateway!");      

      PRINTLN;
      
      delay(10000);    
  }          
}
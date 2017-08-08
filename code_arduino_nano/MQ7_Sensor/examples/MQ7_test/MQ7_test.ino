#include "MQ7_Sensor.h"

//MQ7 MQ7_Sensor(4,A2);

//PIN CONFIG, PWM is on pin D5, Pin A2 is for reading
MQ7 MQ7_Sensor(5,2);

int state = -1;
int co = -1;

void setup() {
  Serial.begin(38400);
}

void loop() {
  state = MQ7_Sensor.get_preheat_state();
  Serial.println("60 sec pre-heat 5V stage 1");


  while (state != 3){
    
    Serial.println(state);   
    delay(1000);
    state = MQ7_Sensor.get_preheat_state();
  }
  Serial.println("90 sec pre-heat 1.4V done");
  
  MQ7_Sensor.scan();
  
  co = MQ7_Sensor.get_CO_concentration();

  Serial.print("CO : ");  
  Serial.println(co);
  
  delay(50000000);
}

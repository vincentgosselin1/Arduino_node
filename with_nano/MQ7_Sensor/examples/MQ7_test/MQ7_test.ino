#include "MQ7_Sensor.h"

MQ7 MQ7_Sensor(4,A2);

int state = -1;
int co = -1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  state = MQ7_Sensor.get_preheat_state();
  while (state != 3){
    
    Serial.println(state);   
    delay(1000);
    state = MQ7_Sensor.get_preheat_state();
  }
  
  MQ7_Sensor.scan();
  
  co = MQ7_Sensor.get_CO_concentration();

  Serial.print("CO : ");  
  Serial.println(co);
  
  delay(50000000);
}

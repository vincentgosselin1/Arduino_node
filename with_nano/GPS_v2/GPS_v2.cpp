//GPS_v2.cpp

#include "GPS_v2_library.h"

//Fil bleu sur D4 et fil vert sur D3 
//GPS gps_sensor(4,3);

//Maintenant, Fil bleu (TX) sur D8 , fil vert (RX) sur D9.
GPS gps_sensor(8,9);

float lat;
float lon;
void setup()
{
  Serial.begin(38400);
}

void loop()
{
 
 delay(5000);
  if(gps_sensor.scan()){
    lat = gps_sensor.get_lat();
    lon = gps_sensor.get_lon();
    
    Serial.print("LAT : ");
    Serial.print(lat,6);//6 decimals.
    Serial.print("  LON : ");
    Serial.println(lon,6);
  }
  
  else{
    Serial.println("NO CONNECTION   ");
  }
    
    
}

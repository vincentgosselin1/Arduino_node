#include "GPS_Library.h"
#include <SoftwareSerial.h>
#include <TinyGPS.h>

//Fil bleu sur D4 et fil vert sur D3
GPS gps_sensor(4,3);
float lat;
float lon;
void setup()
{
  Serial.begin(115200);

}

void loop()
{
 
  if(gps_sensor.scan()){
    lat = gps_sensor.get_lat();
    lon = gps_sensor.get_lon();
    
    Serial.print("LAT : ");
    Serial.print(lat);
    Serial.print("  LON : ");
    Serial.println(lon);
  }
  
  else{
    Serial.println("NO CONNECTION   ");
  }
    
    
}

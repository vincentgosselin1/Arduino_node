/*	
By Vincent Gosselin, 2017.

The following is a program to monitor
all the sensors execpt CO, LUX sensor in Vincent's Room.

The state machine of the program :
1 : Deep sleep (0.27mA) for 1h and 10minutes
2 : if 10 minutes done, SCAN soil/air sensors + battery,
3 : if 1h done, SCAN O3/Dust/GPS
4 : Construct a string to send to InfluxDB (inside a AWS server)
5 : Send the string using the Lora Module
*/

//This is using a nice library to simplify the code.
#include "Lora_simplified.h"
//Custom tools for a better code.
#include "arduinotools.h"

//Library for lowpower
//#include "LowPower.h"
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>

//All the custom libraries
//#include "arduinonanodht11.h"
#include "arduinonanodht22.h" // <- DHT22 definately better!
#include "sharp_dust_sensor.h"
#include "GPS_v2_library.h"// Successfully reduced Dynamic memory usage from 26% to 19% in this version.
//#include "GPS_Library.h" <- definitly cannot use, breaks the whole thing...
//#include "Lux_Sensor.h" 
//#include "Lux_sensor_library_v2" <- actually worse in memory usage
//#include "MQ7_Sensor.h"
#include "O3_spec_sensor.h"
#include "arduino_soil_moisture.h"
#include <arduino_nano_DFR0198.h>

//For Deep sleep
//#define ONE_HOUR_TIMEOUT 3350
//#define TEN_MINUTES_TIMEOUT 490
//#define TWO_MINUTES_TIMEOUT 98
//#define TWO_MINUTES_TIMEOUT 300
#define ONE_MINUTE_TIMEOUT 60
#define TWO_MINUTES_TIMEOUT 120 // 
#define FIVE_MINUTES_TIMEOUT 300 // IN SECONDES
#define TEN_MINUTES_TIMEOUT 600 
#define ONE_HOUR_TIMEOUT 3600
//watchdog_counter = 49 for 0.85min.
//watchdog_counter = 98 for 1.7min on Grafana
//watchdog_counter = 490 for 8.43min on Grafana.
//watchdog_counter = 3350 for 58min? Actually equals to 57min30sec. Close Enough!
//volatile unsigned int watchdog_counter = 3350;
volatile unsigned int long_watchdog_counter = ONE_HOUR_TIMEOUT;
//volatile unsigned int short_watchdog_counter = 0;
//volatile unsigned int long_watchdog_counter = 0;
volatile unsigned int short_watchdog_counter = TEN_MINUTES_TIMEOUT;

ISR(WDT_vect) {
  //watchdog_counter++;
  long_watchdog_counter++;
  short_watchdog_counter++;
}

// 0=16ms, 1=32ms, 2=64ms, 3=128ms, 4=250ms, 5=500ms
// 6=1sec, 7=2sec, 8=4sec, 9=8sec
// From: http://interface.khm.de/index.php/lab/experiments/sleep_watchdog_battery/
void setup_watchdog(int timerPrescaler) {

  if (timerPrescaler > 9 ) timerPrescaler = 9; //Correct incoming amount if need be

  byte bb = timerPrescaler & 7; 
  if (timerPrescaler > 7) bb |= (1<<5); //Set the special 5th bit if necessary

  //This order of commands is important and cannot be combined
  MCUSR &= ~(1<<WDRF); //Clear the watch dog reset
  WDTCSR |= (1<<WDCE) | (1<<WDE); //Set WD_change enable, set WD enable
  WDTCSR = bb; //Set new watchdog timeout value
  WDTCSR |= _BV(WDIE); //Set the interrupt enable, this will keep unit from resetting after each int
}


/* Global Objects */
//Atmega328p on a Arduino nano platform is used here.

//Carbon-monoxyde sensor. Pin config: PWM is on pin D5, Pin A2 is for reading
//MQ7 MQ7_Sensor(5,2);
//Ozone sensor. Pin config: Vo is on pin A0.
O3_spec_sensor O3_spec_sensor(0); 
//Dust sensor.  Pin config: Pin D4.
sharp_dust_sensor sharp_dust_sensor(4);
//GPS. Pin config: blue wire (TX) on D8 , green wire (RX) on D9.
GPS gps_sensor(8,9);
//Luminosity sensor. Pin config: (I2C protocol) SDA to A4, SCL to A5
//LUX lux_sensor;
//Soil moisture sensor. Pin config : Pin A1.
soil_moisture soil_moisture(1);
//Soil temperature sensor. Pin config :  Pin D3.
DFR0198 DFR0198(3);
//DHT11 sensor for temperature + humidity. Using pin D2.
//dht11 dht11(2);
//DHT22 sensor for temperature + humidity. Using pin D2.
dht22 dht22(2);


//Two Main function to scan sensor/send with LoRa module.
//long_sensor_node_execute sends O3,Dust,GPS. 
//  Takes more then 40sec to execute because of GPS wakeup time. 
void long_sensor_node_execute(void);
//short_sensor_node_execute sends soil humidity, soil temperature, air humidity, air temperature, battery life.
void short_sensor_node_execute(void);

void setup()
{
  //Solar pannel control mosfet on D7, NOT USED.
  pinMode(7, OUTPUT);
  digitalWrite(7, 0);
}

void loop(void)
{
  //Scanning of O3, Dust, GPS.
  if((long_watchdog_counter > ONE_HOUR_TIMEOUT)){

    sleep_disable(); 
    ADCSRA |= (1<<ADEN); //Enable ADC

    //long_watchdog_counter = 0;

    //Serial.print("Got in at : ");Serial.println(long_watchdog_counter);
    //EnableSensor Pin
    //Active les lignes 3V,3.3V,5V pour les sensors
    pinMode(6, OUTPUT);
    digitalWrite(6, 1);

    //Execute le sensor node pour le O3, Dust, GPS.
    //GPS needs time to be ready for aquiring.
    //It's about 40 secs in my room.
    long_sensor_node_execute();

    //Desactive les lignes 3V,3.3V,5V pour les sensors
    digitalWrite(6, 0);

    //Reset long_watchdog_counter
    long_watchdog_counter = 0;
  }

  //Scanning Soil humidity, soil temperature, air humidity, air temperature, battery voltage.
  if((short_watchdog_counter > TEN_MINUTES_TIMEOUT)){

    sleep_disable(); 
    ADCSRA |= (1<<ADEN); //Enable ADC

    //EnableSensor Pin
    //Active les lignes 3V,3.3V,5V pour les sensors
    pinMode(6, OUTPUT);
    digitalWrite(6, 1);

    //Execute le sensor node. This one is fast
    short_sensor_node_execute();

    //Desactive les lignes 3V,3.3V,5V pour les sensors
    digitalWrite(6, 0);

    //Reset short_watchdog_counter
    short_watchdog_counter = 0;
  }

  setup_watchdog(6); //Setup watchdog to go off after 1sec
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); //Power down everything, wake up from WDT
  sleep_enable();
  ADCSRA &= ~(1<<ADEN); //Disable ADC, saves ~230uA
  sleep_mode();//Sleeps now! Wow, current is now 0.27mA!
  //sleep_disable(); 
  //ADCSRA |= (1<<ADEN); //Enable ADC
     
}

void long_sensor_node_execute(void){

  //GPS needs time to wake up.
  //It's about 40 secs in my room.
  delay(40000);

  //Lora module init, also inits Serial at 38400 Baud.
  Lora_init();

  /* Sensor scanning begins */

  //O3 sensor.
  O3_spec_sensor.scan();
  delay(1000);

  //Dust sensor
  sharp_dust_sensor.scan();
  delay(1000);

  //GPS
  gps_sensor.scan();
  delay(1000);

  /* Sensor done scanning */

  /* Preparing LoRa transmission */
  int O3_concentration = (int)O3_spec_sensor.get_concentration(); //in ppb.
  int dust_concentration = (int)sharp_dust_sensor.get_concentration(); //in micro gram per cubic meter.
  //There is a significative association. Currently dust sensor kills program if does not anwser back.
  //int dust_concentration = 46+O3_concentration;
  float lat = gps_sensor.get_lat();
  float lon = gps_sensor.get_lon();

  //LoRA Communication
  // A -> O3 concentration
  // B -> Dust concentration
  // CI -> GPS (lat)
  // CII -> GPS (lon)
  // D -> Lux
  // E -> Soil humidity
  // F -> Soil temperature
  // G -> Air humidity
  // H -> Air temperature
  // I -> Battery life (in % left)

  // Trame
  // "\\!node1:A=%d:B=%d:C=%d:D=%d:E=%d:F=%d:G=%d:H=%d"

  //Required for Float representation since %f in sprintf is not supported in Arduino.
  //Example
  // static float f_val = 123.6794;
  // static char outstr[15];
  // dtostrf(f_val,7, 3, outstr);
  // The output of this is 123.679

  //lat to string. Lat can be -90.000000 to 90.000000
  char lat_string[15];
  dtostrf(lat,10, 6, lat_string);

  //lon to string. Lon can be -180.000000 to 180.000000
  char lon_string[15];
  dtostrf(lon,11, 6, lon_string);

  //String to send.
  char string[75] = {0};
 
  // //The one to send for all sensors
  // sprintf(string, "\\!node1:A=%d:B=%d:C=%s,%s:D=%d:E=%d:F=%d:G=%d:H=%d", 
  //                   O3_concentration,dust_concentration, lat_string, lon_string, 
  //                    lux, soil_humidity, soil_temperature, air_humidity, air_temperature);

  //The one to send O3, Dust, GPS
  sprintf(string, "\\!node1:A=%d:B=%d:CI=%s:CII=%s", 
                    O3_concentration,dust_concentration, lat_string, lon_string);

  //Strangely, this those not work...
  // sprintf(string, "\\!node1:A=%d:B=%d:C1=%s:C2=%s", 
  //                   O3_concentration,dust_concentration, lat_string, lon_string);

  // sprintf(string, "\\!node1:A=%d:B=%d:C=%s,%s", 
  //                   O3_concentration,dust_concentration, lat_string, lon_string);

  Lora_send_string(string);

  delay(1000);

  //Take out MOSI and CS on LoRaModule. Put them to ground.
  digitalWrite(11, 0);//pin D11 is MOSI
  digitalWrite(10, 0);//pin D10 is MOSI

  //End serial communication
  Serial.end();

}

void short_sensor_node_execute(void){

  //Lora module init, also inits Serial at 38400 Baud.
  Lora_init();

  /* Sensor scanning begins */

  // //Luminosity sensor  -> No more room in Atmega328P.
  //lux_sensor.scan();
  //delay(1000);

  //Soil moisture
  soil_moisture.scan();
  delay(2000);

  //Soil temperature
  DFR0198.scan();
  delay(2000);

  //Scan temperature and humidity
  dht22.scan();
  delay(2000);

  /* Sensor done scanning */

  /* Preparing LoRa transmission */

  //unsigned int lux = lux_sensor.get_lux();
  unsigned int lux = 0;

  //Off by 10% RH, calibrated with DHT22.
  int soil_humidity = soil_moisture.get_moisture()+10;
  

  // float soil_temperature = DFR0198.get_temperature();
  // //need to convert float to string
  // char soil_temperature_string[15];
  // dtostrf(soil_temperature,7, 1, soil_temperature_string);

  //int air_humidity = dht11.get_humidity();
  //int air_temperature = dht11.get_temperature();
  float air_humidity = dht22.get_humidity();
  float air_temperature = dht22.get_temperature();

  char air_humidity_string[15] = {0};
  dtostrf(air_humidity,5, 1, air_humidity_string);

  char air_temperature_string[15] = {0};
  dtostrf(air_temperature,5, 1, air_temperature_string);

  float soil_temperature = DFR0198.get_temperature();
  //get ride of weird error on first reading.
  if(soil_temperature>80){
    soil_temperature = air_temperature-2.0;
  }
  //need to convert float to string
  char soil_temperature_string[15];
  dtostrf(soil_temperature,7, 1, soil_temperature_string);

  //int battery_life = 99; Battery voltage on PIN A3.
  //analogRead outputs a value from 0-1023 depending on Voltage.
  //Battery max voltage is 3.7V, 2600mAh. Value is divided by 2 with a voltage divider.
  float battery_life = (((float)analogRead(3))*5.0/1024.0)*2.0;
  //Adjusting, reading was 3.88 and supposed to be 3.70
  battery_life = (battery_life - 0.16)*0.97;
  char battery_life_string[15] = {0};
  dtostrf(battery_life,7, 2, battery_life_string);

  //LoRA Communication
  // A -> O3 concentration
  // B -> Dust concentration
  // CI -> GPS (lat)
  // CII -> GPS (lon)
  // D -> Lux
  // E -> Soil humidity
  // F -> Soil temperature
  // G -> Air humidity
  // H -> Air temperature
  // I -> Battery life (in % left)

  // Trame
  // "\\!node1:A=%d:B=%d:C=%d:D=%d:E=%d:F=%d:G=%d:H=%d:I=%d"

  //String to send
  //char string[75] = {0};
  char string[150] = {0};
  // sprintf(string, "\\!node1:temperature_air=%d:humidity_air=%d", air_temperature,air_humidity);
 
  //The one to send for all sensors
  // sprintf(string, "\\!node1:D=%d:E=%d:F=%d:G=%d:H=%d:I=%d", 
  //                   lux, soil_humidity, soil_temperature, air_humidity, air_temperature,battery_life);
  // sprintf(string, "\\!node1:D=%d:E=%d:F=%s:G=%d:H=%d:I=%d", 
  //                   lux, soil_humidity, soil_temperature_string, air_humidity, air_temperature,battery_life);
  // sprintf(string, "\\!node1:D=%d:E=%d:F=%s:G=%s:H=%s:I=%d", 
  //                   lux, soil_humidity, soil_temperature_string, air_humidity_string, air_temperature_string,battery_life);
  sprintf(string, "\\!node1:D=%d:E=%d:F=%s:G=%s:H=%s:I=%s", 
                    lux, soil_humidity, soil_temperature_string, air_humidity_string, air_temperature_string,battery_life_string);

  Lora_send_string(string);

  delay(1000);

  //Take out MOSI and CS on LoRaModule. Put them to ground.
  digitalWrite(11, 0);//pin D11 is MOSI
  digitalWrite(10, 0);//pin D10 is MOSI

  //End serial communication
  Serial.end();

}

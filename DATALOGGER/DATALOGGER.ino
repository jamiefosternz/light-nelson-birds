/*CONNECTION NOTES
 * DHT22 on pin D3
 * Ublox M8C on i2c
 * Ozone Sensor on UNDEFINED
 * OpenLog on UART
 */

// ********************DEPENDENCIES********************
#include <MicroNMEA.h>                        //Needed to parse GPS data
#include <Wire.h>                             //Needed for i2c to GPS
#include <SparkFun_Ublox_Arduino_Library.h>   //Needed for i2c management for GPS

#include <Adafruit_Sensor.h>                       //Needed to parse temp. sensor
#include <DHT.h>
#include <DHT_U.h>


// ********************INIT OBJECTS********************

//define GPS object
SFE_UBLOX_GPS myGPS;

//define GPS buffer and translater object
char nmeaBuffer[100];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

//define DHT22 object (pin no. and sensor type)
DHT_Unified dht(3, DHT22);



void setup()
{
  //Debug Serial init
  Serial.begin(115200);
  Serial.println("Data Logger \n Jamie Foster\n\n");
  
  //init GPS communication @ i2c
  Wire.begin();

  //init ext. temp sensor
  dht.begin();
  
  
  
  //fail statements
  if (myGPS.begin() == false) //gps check
  {
    Serial.println(F("Ublox GPS not detected at default I2C address."));
    while (1);
  }
  
  if (isnan(event.temperature) //dht22 check
  {
    Serial.println(F("Error reading ext. temp."));
    while(1);
  }
  
  
}

void loop()
{
  myGPS.checkUblox(); //See if new data is available. Process bytes as they come in.

  
}

//Function that gets called to parse NMEA data.  Called from sparkfun_ublox
void SFE_UBLOX_GPS::processNMEA(char incoming)
{
  
  nmea.process(incoming);
}

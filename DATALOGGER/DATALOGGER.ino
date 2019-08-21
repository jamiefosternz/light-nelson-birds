/*CONNECTION NOTES
 * DHT22 on pin D3
 * Ublox M8C on i2c
 * Ozone Sensor on UNDEFINED
 * OpenLog on UART
 */
#define logdelay 10000 //time between logging in ms
#define chipselect = 4 //chipselect for SD


// ********************DEPENDENCIES********************
#include <MicroNMEA.h>                        //Needed to parse GPS data
#include <Wire.h>                             //Needed for i2c to GPS
#include <SparkFun_Ublox_Arduino_Library.h>   //Needed for i2c management for GPS

#include <Adafruit_Sensor.h>                       //Needed to parse temp. sensor
#include <DHT.h>
#include <DHT_U.h>

#include <SPI.h>
#include <SD.h>



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
  while (!Serial) {
    ; 
  }
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
  Serial.println("GPS initialized successfully");
  
  sensors_event_t event;
  if (isnan(event.temperature) //dht22 check
  {
    Serial.println(F("Error reading ext. temp."));
    while(1);
  }
  Serial.println("DHT22 initialized successfully");
  
  if (!SD.begin(chipSelect))   //SD card check
  {  
    Serial.println(F("Card failed, or not present"));
    while (1);
  }
  Serial.println("SD card initialized successfully");
  
  myGPS.checkUblox();
  while(nmea.isValid != true)
  {
    Serial.println("No GPS fix");
    delay(1000);
    myGPS.checkUblox();
  }
  
}

void loop()
{
  myGPS.checkUblox(); //See if new data is available. Process bytes as they come in.
  if (logtime => millis())
  {
    log();
    logtime = millis() + logdelay;
  }
}

void log()
{
  sensors_event_t event;              //get DHT22 temp and store in local
  float ext_temp = event.temperature;
  
  if (nmea.isValid() == true)                       //Get GPS info
  {
    String fix = "true";
    long latitude = nmea.getLatitude() / 1000000;
		long longitude = nmea.getLongitude() / 1000000;
    
    long altitude;                       //Get altitude.  defaults to -1 if no valid fix.
    if (nmea.getAltitude(altitude)) {}
    else 
    {
      altitude = -1;
    }
  }
  else
  {
    String fix = "false";
    long latitude = -1;
    long longitude = -1;
    long altitude = -1;
  }
  
  String date = String(nmea.getYear()) +"/"+ String(nmmea.getMonth()) +"/"+ string(nmea.getDay());
  String time = String(nmea.getHour()) +":"+ String(nmea.getMinute()) +":"+ String(nmea.getSecond());
  
  //OZONE GOES HERE
  
  
  
  String dataString = ""
  dataString += String(time);
  dataString += ",";
  dataString += String(ext_temp);
  dataString += ",";
  dataString += String(int_temp);
  dataString += ",";
  dataString += String(ozone);
  dataString += ",";
  dataString += String(latitude);
  dataString += ",";
  dataString += String(longitude);
  dataString += ",";
  dataString += String(altitude);
  dataString += ",";
}

//Function that gets called to parse NMEA data.  Called from sparkfun_ublox
void SFE_UBLOX_GPS::processNMEA(char incoming)
{
  
  nmea.process(incoming);
}

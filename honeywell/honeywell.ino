#include<SPI.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int Addr = 0x27;
const int chipSelect = 4;
float humidity , temp , cTemp ;
float refresh_rate = 0.0; //Datalogger Refresh Rate
long id = 1;              //Store the id# of our reading
String dataString ;

  int year,month,date,hour,minute,second;
void setup()
{ // open the USBSerial port

  Wire.begin();
  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  Serial.println("Setup OK");


  //Write Log.csv File Header
  File logFile = SD.open("LOG.csv", FILE_WRITE);
  if (logFile)
  {
    logFile.println(", ,"); //Just a leading blank line, incase there was previous data
    String header = "ID,Date, Month, year, Hour, Minute, Second, Humidity, Temperature";
    logFile.println(header);
    logFile.close();
    Serial.println(header);
  }
  else
  {
    Serial.println("Couldn't open log file");
    return;
  }

}

void loop() {

  unsigned int data[4];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
  // Request 4 bytes of data
  Wire.requestFrom(Addr, 4);

  // Read 4 bytes of data
  // humidity msb, humidity lsb, temp msb, temp lsb
  if (Wire.available() == 4)
  { data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
  }

  // Convert the data to 14-bits
  humidity = ((((data[0] & 0x3F) * 256) + data[1]) * 100.0) / 16383.0;
  temp = ((data[2] * 256) + (data[3] & 0xFC)) / 4;
  cTemp = (temp / 16384.0) * 165.0 - 40.0;


  // Output data to serial monitor
  Serial.print("Relative Humidity :");
  Serial.print(humidity);
  Serial.println(" %RH");
  Serial.print("Temperature in Celsius :");
  Serial.print(cTemp);
  Serial.println(" C");
  Serial.println("=============================================================== ");
  Serial.println(" ");
  delay(500);
  readrtc();

  datalog();
}


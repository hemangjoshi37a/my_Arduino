
//Jeremey Blum - Tutorial 11
//http://www.jeremyblum.com/2011/04/05/tutorial-11-for-arduino-sd-cards-and-datalogging/
//iteadstudio SDCard Shield v1.0

#include <SD.h>

//SPI Settings
//MOSI, MISO, SCLK Set by default
int CS_pin = 4;
//int pow_pin = 8;

//sensor analog inputs
int voltage_pin = 0;
int current_pin = 1;
int sensorCal = 531; //531 manual input raw input at zero amps for Hall Sensor
int sensorSpec = 40; //Hall Sensor, 40 mV per Amp


void setup()
{
 Serial.begin(9600);
 Serial.println("Initializing Card");
 //CS Pin is an output
 pinMode(CS_pin, OUTPUT);
 
 //Card will Draw float refresh_rate = 0.0; //Datalogger Refresh Rate
long id = 1;              //Store the id# of our reading

Power from Pin 8, so set it high
 //pinMode(pow_pin, OUTPUT);
 //digitalWrite(pow_pin, HIGH);
 
 //Check if card ready
 if(!SD.begin(CS_pin))
 {
   Serial.println("Card Failed");
   return;
 }
 Serial.println("Card Ready");
 
 //Read the configuration information (COMMANDS.txt)
 File commandFile = SD.open("COMMANDS.txt");
 if (commandFile)
 {
   Serial.println("Reading Command File");
   
   float decade = pow(10, (commandFile.available() - 1));
   while(commandFile.available())
   {
     float temp = (commandFile.read() - '0');
     refresh_rate = temp*decade+refresh_rate;
     decade = decade/10;
   }
   Serial.print("Refresh Rate = ");
   Serial.print(refresh_rate);
   Serial.println("ms");
 }
 else
 {
   Serial.println("Could not read commande file.");
   return;
 }
 
 //Write Log.csv File Header
 File logFile = SD.open("LOG.csv", FILE_WRITE);
 if (logFile)
 {
   logFile.println(", ,"); //Just a leading blank line, incase there was previous data
   String header = "ID, Voltage, Current";
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

void loop()
{  

//read voltage divider circuit output r1=10k(really 9.88k) r2=1k
 int voltage_grab = analogRead(voltage_pin);
 float voltRatio = voltage_grab / 1023.00; //find ratio of reading to convert to v where 1023=5v
 float voltFloat = voltRatio * 5.00 * 11.00 * 100.00; //5v * voltage divider measured ratio 11 * mV conversion 100
 int voltage_reading = voltFloat; //convert float reading to integer for the dataString
 
 //convert hall amp sensor reading to actual current
 int ampRead = analogRead(current_pin); //Read hall sensor output
 ampRead = constrain(ampRead, sensorCal, 1023); //constrain to manual sensor calibration
 int current_reading = ampRead - sensorCal; //Declare new int for conversion
 current_reading = (current_reading * 4.9) / sensorSpec; //4.9 * Analog signal =~ mV, divide by example: "ACS756 spec: 40mV/1A"
 //int hallMv = analogRead(hallIn) * 4.9; //debugging to view mV
 
 
 String dataString = String(id) + ", " + String(voltage_reading) + ", " + String(current_reading);
 
 //Open a file to write to
 //Only one file can be open at a time
 File logFile = SD.open("LOG.csv", FILE_WRITE);
 if(logFile)
 {
   logFile.println(dataString);
   logFile.close();
   Serial.println(dataString);
 }
 else
 {
   Serial.println("Couldn't access file");
 }
 //increment ID #
 id++;
 
 delay(refresh_rate);
}

 

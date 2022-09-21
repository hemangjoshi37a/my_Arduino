
void datalog() {

  dataString = String(id) + ", " + String(date) + ", " + String(month)+ ", " + String(year)+ ", " + String(hour)+ ", " + String(minute)+ ", " + String(second)+ ", " + String(humidity)+ ", " + String(cTemp);
 
  File logFile = SD.open("LOG.csv", FILE_WRITE);
  if (logFile)
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

}




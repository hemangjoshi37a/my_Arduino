
#include <Wire.h>
#include "SSD1306.h"
#include <SPI.h>
#include "SSD1306Spi.h"
#include "images.h"
#include <ESP8266WiFi.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

#include <ESP8266WiFi.h>

//how many clients should be able to telnet to this ESP8266
#define MAX_SRV_CLIENTS 1
const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";
IPAddress ip(192, 168, 0, 177);
WiFiServer server(23);
WiFiClient serverClients[MAX_SRV_CLIENTS];
byte a, alst;
String astr;
unsigned int count = 1;

// Initialize the OLED display using SPI
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D2 -> DC
// D8 -> CS
SSD1306Spi        display(D0, D3, D8);

#define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;
int16_t adc0, adc1, adc2, adc3;
int menu = 0;
int progress = 0;
int proglast = 0;
int progct = 10;
int amax = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  pinMode(D8, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  // Initialising the UI will init the display too.
  display.init();

  //display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  ads.begin();

  //////////////////////////////////////////

  a = 0;
  alst = 1;
  Serial1.begin(115200);
  WiFi.begin(ssid, password);
  Serial1.print("\nConnecting to "); Serial1.println(ssid);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
  if (i == 21) {
    Serial1.print("Could not connect to"); Serial1.println(ssid);
    while (1) delay(500);
  }
  //start UART and the server
  server.begin();
  server.setNoDelay(true);
  Serial1.print("Ready! Use 'telnet ");
  Serial1.print(WiFi.localIP());
  Serial1.println(" 23' to connect");
  a = (byte)analogRead(A0);
  astr = String(a);

}

void drawFontFaceDemo() {
  // Font Demo1
  // create more fonts at http://oleddisplay.squix.ch/
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Hello world");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 10, "Hello world");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 26, "Hello world");
}

void drawFontFaceDemo2() {
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  // display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 10, "My IP is :");
  display.drawString(0, 30, IpAddress2String(WiFi.localIP()));

}


void drawTextFlowDemo() {
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawStringMaxWidth(0, 0, 128,
                             "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
}

void drawTextAlignmentDemo() {
  // Text alignment demo
  display.setFont(ArialMT_Plain_10);
  // The coordinates define the left starting point of the text
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 10, "Left aligned (0,10)");
  // The coordinates define the center of the text
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 22, "Center aligned (64,22)");
  // The coordinates define the right end of the text
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 33, "Right aligned (128,33)");
}

void drawRectDemo() {
  // Draw a pixel at given position
  for (int i = 0; i < 10; i++) {
    display.setPixel(i, i);
    display.setPixel(10 - i, i);
  }
  display.drawRect(12, 12, 20, 20);
  // Fill the rectangle
  display.fillRect(14, 14, 17, 17);
  // Draw a line horizontally
  display.drawHorizontalLine(0, 40, 20);
  // Draw a line horizontally
  display.drawVerticalLine(40, 0, 20);
}

void drawCircleDemo() {
  for (int i = 1; i < 8; i++) {
    display.setColor(WHITE);
    display.drawCircle(32, 32, i * 3);
    if (i % 2 == 0) {
      display.setColor(BLACK);
    }
    display.fillCircle(96, 32, 32 - i * 3);
  }
}

void drawProgressBarDemo() {
  //////////////////////////////////////////////////

  display.setFont(ArialMT_Plain_16);
  for (int i = 0; i <= 100; i++) {
    adc0 = ads.readADC_SingleEnded(0);
    progress += adc0 ;
  }

  progress = progress / 100;
  progress = progress - proglast;

  if (amax < progress) {
    amax = progress;
  }

  //float bari = (progress / amax) * 100;

  // draw the progress bar
  display.drawProgressBar(12, 0, 120, 10, progress);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 11, String(progress) + " ml");

  ///reset
  if (proglast < progress - 50 || proglast > progress + 50) {
    progct = 10;
  }
  else {
    progct--;
    progct = progct * 10;
    display.drawProgressBar(12, 31, 100, 10, progct);
    progct = progct / 10;
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 43,  "Resetting in " + String(progct));
    if (progct <= 0) {
      proglast = progress;
      progct = 10;
    }
  }
}

void drawImageDemo() {
  // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
  // on how to create xbm files
  display.drawXbm(0, 0, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
}

Demo demos[] = {drawProgressBarDemo, drawImageDemo, drawFontFaceDemo2};
//Demo demos[] = {drawFontFaceDemo, drawTextFlowDemo, drawTextAlignmentDemo, drawRectDemo, drawCircleDemo, drawProgressBarDemo, drawImageDemo};
int demoLength = (sizeof(demos) / sizeof(Demo));
long timeSinceLastModeSwitch = 0;



void loop() {

  //////////////////////////////////////////////////////////////
  // clear the display
  display.clear();
  // draw the current demo method
  demos[demoMode]();

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  display.display();

  //    if (millis() - timeSinceLastModeSwitch > DEMO_DURATION) {
  //      demoMode = (demoMode + 1)  % demoLength;
  //      timeSinceLastModeSwitch = millis();
  //    }
  // demoMode = 1;
  counter++;
  delay(10);

  a = digitalRead(D8);

  if (a == 0) {
    menu++;
    demoMode = menu % 3;
    delay(250);
    while (a == 1) {
      delay(1);
    }
  }

}


String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") + \
         String(ipAddress[1]) + String(".") + \
         String(ipAddress[2]) + String(".") + \
         String(ipAddress[3])  ;
}
//sj@element14.com

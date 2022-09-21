
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include <SPI.h> // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Spi.h"
//#include "ESP8266.h"
#include "images.h"
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
// Initialize the OLED display using SPI
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D3 -> DC
// D8 -> CS
SSD1306Spi        display(D0, D3, D8);

#define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;

int16_t adc0, adc1, adc2, adc3;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  ads.begin();
  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  // Initialising the UI will init the display too.
  display.init();

  //display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);


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

  return;
}

void drawTextFlowDemo() {
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawStringMaxWidth(0, 0, 128,
                             "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
  return;
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
  return;
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
  return;
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
  return;
}

void drawProgressBarDemo() {
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("AIN2: "); Serial.println(adc2);
  Serial.print("AIN3: "); Serial.println(adc3);
  Serial.println(" ");

  int progress = (adc0 / 5) % 100;

  // draw the progress bar
  display.drawProgressBar(12, 0, 100, 10, progress);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "kg:");
  return;
}

void drawImageDemo() {
  // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
  // on how to create xbm files
  display.drawXbm(0, 0, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
  return;
}


Demo demos[] = {drawFontFaceDemo, drawTextFlowDemo, drawTextAlignmentDemo, drawRectDemo, drawCircleDemo, drawProgressBarDemo, drawImageDemo};
int demoLength = (sizeof(demos) / sizeof(Demo));
long timeSinceLastModeSwitch = 0;




void loop() {

  delay(1000);

  // clear the display
  display.clear();
  // draw the current demo method
  //   demos[demoMode]();

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  display.display();
  // drawProgressBarDemo() ;


  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("AIN2: "); Serial.println(adc2);
  Serial.print("AIN3: "); Serial.println(adc3);
  Serial.println(" ");

  int progress0 = (adc0 / 5) % 100;
  int progress1 = (adc1 / 5) % 100;
  int progress2 = (adc2 / 5) % 100;
  int progress3 = (adc3 / 5) % 100;

  display.clear();
  // draw the progress bar
  display.drawProgressBar(12, 0, 100, 10, progress0);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress0) + "kg:");


  if (millis() - timeSinceLastModeSwitch > DEMO_DURATION) {
    demoMode = (demoMode + 1)  % demoLength;
    timeSinceLastModeSwitch = millis();
  }
  counter++;
  delay(10);


}

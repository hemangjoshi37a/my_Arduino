# menusystem

An arduino library for implementing a menu system.

## Documentation

Other than the examples included in the library, the following pages might be
useful to you:

* [Arduino forum post](http://arduino.cc/forum/index.php/topic,105866.0.html)
* [Arduino Menu System Library](http://www.jonblack.me/arduino-menu-system-library/)

## Contribution

If you'd like to contribute to `arduino-menusystem`, please submit a
pull-request.

## Donate

* Bitcoin:  1D4MBvrR9w4yVEHvQbzM8WAuJjDdzp7trA
* Ethereum: 0x75804bb16c8177D919ea54a35980c9202F294A10

## Changelog

**3.0.0 - 24-08-2017**

* Factor out rendering a menu from its implementation
* Add `NumericMenuItem` and `BackMenuItem`
* Add `Menu` callback method
* `MenuSystem` creates its own root menu
* Hide non-api methods by making them private
* Deprecate `Menu::get_selected`

**2.1.1 - 22/03/2016**

* Fix regression - add reset option to select

**2.1.0 - 20/03/2016**

* Fix bug resetting the menu. Now possible via `reset()`

**2.0.2 - 23/01/2016**

* Fix deprecated conversion from string constant to char*
* Add Sure Electronics animated LED matrix example

**2.0.1 - 16/08/2015**

* Add Sure Electronics LED Matrix example

**2.0.0 - 14/08/2015**

* Add LCD Nav Keypad example from (thanks to @SauleVire)
* Remove AUTHORS file: too much hassle to maintain
* Add library.properties

**1.0.1 - 20/13/2013**

* Renamed project to `arduino-menusystem`;
* Fix buffer overflow when adding a menu;
* Menu components are now dynamically allocated (previously it was fixed at
  five items).

**1.0.0 - 15/12/2013**

* Selected menu item can be remembered (thanks to @KipK)
* Examples for serial and LCDs (thanks to @niesteszeck)
* Add AUTHORS file

**0.3.0 - 23/03/2013**

* Merged in another minor improvement provided by @thomasjfox:
 * Add the ability to loop through a menu in `prev()` and `next()`

**0.2.0 - 18/03/2013**

* Merged in minor improvements provided by thomasjfox
 * `get_menu_component()`: Use 'byte' instead of 16bit integer for index
 * Add return value to `MenuSystem.back()`
 * Prevent memory corruption by inserting too many items
 * Whitespace cleanup

**0.1.0 - 25/05/2012**

* Added support for displaying all current menu items (thanks to arcachofo)
* Added this readme

Note: The changes made for this release break backwards compatability. The
issues are relatively easy to fix.


# Arduino and ESP8266 (or NodeMCU) projects

## [IoT_LED_over_ESP8266_NodeMCU : Turn LED on and off using web server hosted on a nodemcu or esp8266](https://github.com/hemangjoshi37a/my_Arduino/tree/master/IoT_LED_over_ESP8266_NodeMCU)

![image](./IoT_LED_over_ESP8266_NodeMCU/ESP8266-based-Webserver-to-Control-LED-from-Webpage.jpg)

## [ESP8266_NodeMCU_BasicOTA : Simple OTA (Over The Air) upload code from Arduino IDE using WiFi to NodeMCU or ESP8266](https://github.com/hemangjoshi37a/my_Arduino/tree/master/ESP8266_NodeMCU_BasicOTA)  

![image](./ESP8266_NodeMCU_BasicOTA/maxresdefault.jpg)

## [IoT_CSV_SD : Read analog value of Voltage and Current and write it to SD Card in CSV format for Arduino, ESP8266, NodeMCU etc](https://github.com/hemangjoshi37a/my_Arduino/tree/master/IoT_CSV_SD)  

![image](./IoT_CSV_SD/ESP8266-Data-Logger-to-Upload-Data-on-Webserver.jpg)

## [Honeywell_I2C_Datalogger : Log data in A SD Card from a Honeywell I2C HIH8000 or HIH6000 series sensor having external I2C RTC clock](https://github.com/hemangjoshi37a/my_Arduino/tree/master/Honeywell_I2C_Datalogger)

[![Transmitter](https://img.youtube.com/vi/MC9E-f79TsQ/0.jpg)](https://www.youtube.com/watch?v=MC9E-f79TsQ)

[![DigiTemp](https://img.youtube.com/vi/ySsQuUL6oOM/0.jpg)](https://www.youtube.com/watch?v=ySsQuUL6oOM)

## [IoT_Load_Cell_using_ESP8266_NodeMC : Read ADC value from High Precision 12bit ADS1015 ADC Sensor and Display on SSD1306 SPI Display as progress bar for Arduino or ESP8266 or NodeMCU](https://github.com/hemangjoshi37a/my_Arduino/tree/master/IoT_Load_Cell_using_ESP8266_NodeMC)

![image](./IoT_Load_Cell_using_ESP8266_NodeMC/FU01LUUJHIA31PU.webp)

## [IoT_SSD1306_ESP8266_NodeMCU : Read from High Precision 12bit ADC seonsor ADS1015 and display to SSD1306 SPI as progress bar in ESP8266 or NodeMCU or Arduino](https://github.com/hemangjoshi37a/my_Arduino/tree/master/IoT_SSD1306_ESP8266_NodeMCU)  

![image](./IoT_SSD1306_ESP8266_NodeMCU/NodeMCU_ESP8266_OLED_Display.png)

## [Libraries needed for this projects](https://github.com/hemangjoshi37a/my_Arduino/tree/master/libraries)  

----------------------------------------------------------------------

### Contact us

Mobile : [+917016525813](tel:+917016525813)
Whatsapp & Telegram : [+919409077371](tel:+919409077371)

Email : [hemangjoshi37a@gmail.com](mailto:hemangjoshi37a@gmail.com)

Place a custom order on hjLabs.in : [https://hjLabs.in](https://hjlabs.in/)

Please contribute your suggestions and corections to support our efforts.

Thank you.

Buy us a coffee for $5 on PayPal ?

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=5JXC8VRCSUZWJ)

----------------------------------------------------------------------

### Checkout Our Other Repositories

- [pyPortMan](https://github.com/hemangjoshi37a/pyPortMan)
- [transformers_stock_prediction](https://github.com/hemangjoshi37a/transformers_stock_prediction)
- [TrendMaster](https://github.com/hemangjoshi37a/TrendMaster)
- [hjAlgos_notebooks](https://github.com/hemangjoshi37a/hjAlgos_notebooks)
- [AutoCut](https://github.com/hemangjoshi37a/AutoCut)
- [My_Projects](https://github.com/hemangjoshi37a/My_Projects)
- [Cool Arduino and ESP8266 or NodeMCU Projects](https://github.com/hemangjoshi37a/my_Arduino)

### Checkout Our Other Products

- [WiFi IoT LED Matrix Display](https://hjlabs.in/product/wifi-iot-led-display)
- [SWiBoard WiFi Switch Board IoT Device](https://hjlabs.in/product/swiboard-wifi-switch-board-iot-device)
- [Electric Bicycle](https://hjlabs.in/product/electric-bicycle)
- [Product 3D Design Service with Solidworks](https://hjlabs.in/product/product-3d-design-with-solidworks/)
- [AutoCut : Automatic Wire Cutter Machine](https://hjlabs.in/product/automatic-wire-cutter-machine/)
- [Custom AlgoTrading Software Coding Services](https://hjlabs.in/product/custom-algotrading-software-for-zerodha-and-angel-w-source-code//)
- [SWiBoard :Tasmota MQTT Control App](https://play.google.com/store/apps/details?id=in.hjlabs.swiboard)

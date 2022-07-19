# E-Motion-chair

## Getting started

Add the following to your arduino IDE: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
Then update the board manager > type esp32 and download/update the boards available.

Follow this tutorial for Webserver:
https://randomnerdtutorials.com/esp32-async-web-server-espasyncwebserver-library/

Use this libary for the sd card:
https://github.com/nhatuan84/esp32-micro-sdcard

Format sd card:

open powershell as admin and: '''format /FS:FAT32 D:''' > change D: to your drive. 

http://www.iotsharing.com/2017/05/how-to-use-arduino-esp32-to-store-data-to-sdcard.html

C:\Users\jgm_6\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.4\variants\esp32s2\pins_arduino.h

static const uint8_t SS    = 10;
static const uint8_t MOSI  = 11;
static const uint8_t MISO  = 13;
static const uint8_t SCK   = 12;
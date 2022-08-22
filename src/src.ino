//importing dependencies
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include ".\conf.h"
#include ".\emotionchair_lib.h"

#include <SPI.h>
#include <SD.h>
#include <HTTPClient.h>
#include <ErriezDS3231.h>
#include <Wire.h>

// Create RTC object
ErriezDS3231 rtc;

//define RTC I2C module pins
#define I2C_SDA 8
#define I2C_SCL 7

time_t count = 0;
AsyncWebServer server(80);
String payload = String("0");
String startOfString = String("/test_");
String endOfString = String(".csv");
int statusCount = 0;
int fileCountOnSD = 0; 

void setup() {
    Serial.begin(115200);

    // Setting pinmode for reading sensors 
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);

    // connecting to RTC module
    delay(500);
    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.setClock(100000);

    //check if SD card is connected
      if (!SD.begin()) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // open sd card and check for amount of files 
  File dir = SD.open("/");
  fileCountOnSD = 0;
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      break;
      }
    entry.close(); 
    fileCountOnSD++;
    };
    Serial.print("fileCountOnSD: ");
    Serial.println(fileCountOnSD);

    //start wifi connection to network in conf.h file
    Serial.print("`trying to connect to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        statusCount++;
        if(statusCount==5){
          ESP.restart();
          }
    }

    // check if wifi connection was succesfull, if so starts webserver
    if (WiFi.status() == WL_CONNECTED){
      Serial.println("");
      Serial.println("WiFi connected.");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());

      HTTPClient http;
  
      Serial.print("Sending request");
    
      http.begin(serverPath.c_str());
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        time_t new_rtc = payload.toInt();
        rtc.setEpoch(new_rtc);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();

      server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/plain", String(state));
      });
      
      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SD, "/index.html", "text/html");
      });
      
      server.on("/files", HTTP_GET, [](AsyncWebServerRequest *request){ 
      request->send(200, "text/plain", String(fileCountOnSD));
      });
      
      server.serveStatic("/", SD, "/");
      server.begin();
      }else {
    Serial.print("unable to connect to wifi");
  }
    //File dir =  SD.open("/");
    //printDirectory(dir, 0);
  }

void loop() {

  // set count to current UNIX epoch (either from internet or rtc module)
  count = rtc.getEpoch();
  String path = startOfString + String(count) + endOfString;
  File csvFile = SD.open(path, FILE_WRITE);

  //read 25 points 
  int result_array[9];
  for(int j =0; j<25; j++){
    //read voltage (ADC) for every sensor
    for(int i =0; i<9; i++){
      //set_sensor_to_read(i); //not used, reserve vor Mux Mux setup
      int result = read_sensor(i);
      result_array[i] = result;
      csvFile.print(result);
      csvFile.print(",");
      }
    delay(40);//25Hz sampling
    csvFile.println("");
  }

  if(csvFile){
  csvFile.flush();
  csvFile.close();
  }
  //Check the time
  Serial.println(millis());
  }

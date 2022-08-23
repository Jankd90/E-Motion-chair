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
bool status = true;


int setSampleFrequency = 10;
int sampleFrequency = setSampleFrequency;
int setSampleTime = 60;
int sampleTime = setSampleTime;
File csvFile;

const int arysz = 5;
int sampleSet[] = {60,180,300,600,900};
int frequencySet[] = {1,5,10,25,50};

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
    //start wifi connection to network in conf.h file
    Serial.print("`trying to connect to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        statusCount++;
        if(statusCount==5){
          Serial.print("Not connected");
          break;
          //ESP.restart();
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
            server.on("/1", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/plain", String(setSampleTime));
      });
            server.on("/2", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/plain", String(setSampleFrequency));
      });
      
        server.on("/samplefrequency/1", HTTP_GET, [](AsyncWebServerRequest *request){
          setSampleFrequency = frequencySet[0];
          request->send(200, "text/plain", String(setSampleFrequency));
      });
        server.on("/sampleminutes/1", HTTP_GET, [](AsyncWebServerRequest *request){
          setSampleTime = sampleSet[0];
          request->send(200, "text/plain", String(setSampleTime));
      });

        server.on("/samplefrequency/5", HTTP_GET, [](AsyncWebServerRequest *request){
          setSampleFrequency = frequencySet[1];
          request->send(200, "text/plain", String(setSampleFrequency));
      });
        server.on("/sampleminutes/3", HTTP_GET, [](AsyncWebServerRequest *request){
          setSampleTime = sampleSet[1];
          request->send(200, "text/plain", String(setSampleTime));
      });

              server.on("/samplefrequency/10", HTTP_GET, [](AsyncWebServerRequest *request){
          setSampleFrequency = frequencySet[2];
          request->send(200, "text/plain", String(setSampleFrequency));
      });
        server.on("/sampleminutes/5", HTTP_GET, [](AsyncWebServerRequest *request){
          setSampleTime = sampleSet[2];
          request->send(200, "text/plain", String(setSampleTime));
      });

              server.on("/samplefrequency/25", HTTP_GET, [](AsyncWebServerRequest *request){
          setSampleFrequency = frequencySet[3];
          request->send(200, "text/plain", String(setSampleFrequency));
      });
        server.on("/sampleminutes/10", HTTP_GET, [](AsyncWebServerRequest *request){
          setSampleTime = sampleSet[3];
          request->send(200, "text/plain", String(setSampleTime));
      });
      
      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SD, "/index.html", "text/html");
      });
      server.serveStatic("/", SD, "/");
      server.begin();
      }else {
    Serial.print("unable to connect to wifi");
  }
  }

void loop() {
 if(status){
  Serial.println("status is active");
  sampleFrequency = setSampleFrequency;
  sampleTime = setSampleTime;
  // set count to current UNIX epoch (either from internet or rtc module)
  count = rtc.getEpoch();
  String path = startOfString + String(count) + endOfString;
  csvFile = SD.open(path, FILE_WRITE);
  }
 else{
  Serial.println("status is inactive");
  sampleFrequency = 1;
  sampleTime = 1;
  }
  int result_array[9];
  //3 minutes....25*180
  unsigned int total = 0;
  for(int j =0; j<sampleFrequency*sampleTime; j++){
    //read voltage (ADC) for every sensor
    for(int i =0; i<9; i++){
      int result = read_sensor(i);
      total += result/9;
      result_array[i] = result;
       if(status){
      csvFile.print(result);
      csvFile.print(",");
       }
      }
     if(status){
      csvFile.println("");
      }
     delay(int((1000/sampleFrequency)-5));//..Hz sampling
     //Detecting presure
     
    //check speed
    Serial.println(".");
    //Serial.println(millis());
  }

  if(csvFile){
  csvFile.close();
  }
  total = total/(sampleFrequency*sampleTime);
  Serial.print(total);
  if(total > 200){
       status = true;
      }
     else{
       status = false;
      }
  //Check the time
  //Serial.print("Time: ");
  //Serial.println(millis());
  Serial.println("");
  Serial.print("total value: ");
  Serial.println(total);
  }

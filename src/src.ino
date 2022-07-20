#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include ".\conf.h"
#include ".\emotionchair_lib.h"

#include <SPI.h>
#include <SD.h>
#include <HTTPClient.h>

int count = 0;
AsyncWebServer server(80);
String payload = String("0");
String startOfString = String("/test_");
String endOfString = String(".csv");
int statusCount = 0;
int fileCountOnSD = 0; 

void setup() {
    Serial.begin(9600);
      if (!SD.begin()) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }
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
    Serial.print("Connecting to ");
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
        count = payload.toInt();
        Serial.println(payload);
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
    
    
    //File dir =  SD.open("/");
    //printDirectory(dir, 0);
}

void loop() {
  String path = startOfString + String(count) + endOfString;
  File csvFile = SD.open(path, FILE_WRITE);
  for(int j =0; j<25; j++){
    for(int i =0; i<10; i++){
      set_sensor_to_read(i);
      int result = read_sensor();
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
  fileCountOnSD++;
  count++;
}

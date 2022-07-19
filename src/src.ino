#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include ".\conf.h"
#include ".\emotionchair_lib.h"
AsyncWebServer server(80);
int state = 0;

void setup() {
    Serial.begin(9600);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/plain", String(state));
    });
    server.begin();
}

void loop() {
  state++;
  delay(1000);
}

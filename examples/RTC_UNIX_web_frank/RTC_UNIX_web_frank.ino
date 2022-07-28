#include <Wire.h>
#include <WiFi.h>
#include <ErriezDS3231.h>
#include <HTTPClient.h>

// Create RTC object
ErriezDS3231 rtc;

#define I2C_SDA 8
#define I2C_SCL 7

// Replace with your network credentials
const char* ssid = "Oneplus";
const char* password = "cashmeoutside";

void setup()
{
  Serial.begin(115200);
      // Initialize serial port
    delay(500);
    Wire.begin(I2C_SDA, I2C_SCL);

    // Initialize I2C
    Wire.begin();
    Wire.setClock(100000);

    // Initialize RTC
    while (!rtc.begin()) {
        Serial.println(F("RTC not found"));
        delay(3000);
    }

  // Set web server port number to 80
  WiFiServer server(80);

    HTTPClient http;

    Serial.print("Sending request");

    String serverPath = "https://currentmillis.com/time/seconds-since-unix-epoch.php";
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
    http.begin(serverPath.c_str());
    int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        time_t new_rtc = payload.toInt();
        Serial.println(payload);
        Serial.println("UNIX time downloaded from internet, setting RTC module");
        rtc.setEpoch(new_rtc);
      }
      
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        Serial.println("UNIX time not recieved from internet, using RTC module memory");
        
      }
      // Free resources
      http.end();

    // Set new time for RTC 12:00:00
    //rtc.setTime(13, 13, 20);

}

void loop()
{
    Serial.println(rtc.getEpoch());
}

#include <Wire.h>
#include <WiFi.h>
#include <ErriezDS3231.h>

// Create RTC object
ErriezDS3231 rtc;

#define I2C_SDA 8
#define I2C_SCL 7


// Replace with your network credentials
const char* ssid = "Verbindingsstraat 6 ";
const char* password = "NietVoorAlgemeenGebruik9754AH!";

// Set web server port number to 80
WiFiServer server(80);

void setup()
{
    // Initialize serial port
    delay(500);
    Wire.begin(I2C_SDA, I2C_SCL);
    Serial.begin(115200);
    while (!Serial) {
        ;
    }

    // Initialize I2C
    Wire.begin();
    Wire.setClock(100000);

    // Initialize RTC
    while (!rtc.begin()) {
        Serial.println(F("RTC not found"));
        delay(3000);
    }

    rtc.setSquareWave(SquareWaveDisable);

    // Set new time for RTC 12:00:00
    //rtc.setTime(13, 13, 20);
}

void loop()
{
    uint8_t hour;
    uint8_t min;
    uint8_t sec;

    // Get time from RTC
    if (!rtc.getTime(&hour, &min, &sec)) {
        Serial.println(F("Get time failed"));
    } else {
        // Print time
        Serial.print(hour);
        Serial.print(F(":"));
        if (min < 10) {
            Serial.print(F("0"));
        }
        Serial.print(min);
        Serial.print(F(":"));
        if (sec < 10) {
            Serial.print(F("0"));
        }
        Serial.println(sec);
    }

    // Wait a second
    delay(1000);
}

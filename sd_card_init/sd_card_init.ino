#include <SPI.h>
#include <mySD.h>


#define SD_PIN_NUM_MISO 13
#define SD_PIN_NUM_MOSI 11
#define SD_PIN_NUM_CLK  12
#define SD_PIN_NUM_CS   10
File root;
const int chipSelect = 13;

void setup()
{
  Serial.begin(115200);
  Serial.print("Initializing SD card...");
  pinMode(SS, OUTPUT);
  //SPI.begin(10, 11, 13, 12);

  //SDClass::begin(uint8_t csPin, int8_t mosi, int8_t miso, int8_t sck) 
  if (!SD.begin(10,11,13,12)) {
    Serial.println("initialization failed!");
    return;
  }
  
  Serial.println("initialization done.");

  root = SD.open("/");
  
  printDirectory(root, 0);
  
  Serial.println("done!");
}

void loop()
{
  // nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
  // Begin at the start of the directory
  dir.rewindDirectory();
  
  while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');   // we'll have a nice indentation
     }
     // Print the 8.3 name
     Serial.print(entry.name());
     // Recurse for directories, otherwise print the file size
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}

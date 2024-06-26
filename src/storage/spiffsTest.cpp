/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-vs-code-platformio-spiffs/  
*********/

#include <Arduino.h>
#include "SPIFFS.h"
 
void setup() {
  Serial.begin(9600);
  
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
  File file = SPIFFS.open("/text.txt");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  
  Serial.println("start");

  Serial.println("File Content:");
  while(file.available()){
    Serial.println("content"); 
    Serial.write(file.read());
  }
  Serial.println("not available"); 
  file.close();
}
 
void loop() {

}
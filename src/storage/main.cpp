#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h" // Include the SPIFFS library

AsyncWebServer server(80);

const char* ssid = "212IntroRobotics";
const char* password = "robot2016";

String getVal() {
  int t = rand();  
  Serial.println(t);
  return String(t);
}

void setup() {
  Serial.begin(11500);

  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);                         // start WiFi interface

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi. Local IP: ");
  Serial.print(WiFi.localIP());       // print IP address of WiFi interface

  // Initialize SPIFFS
  Serial.println("starting SPIFFS");
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount SPIFFS");
    return;
  }

  // Route to serve the web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", getVal().c_str());
    Serial.println(getVal().c_str());
  });
  // Start server 
  server.begin(); 

}

void loop() {
  
}


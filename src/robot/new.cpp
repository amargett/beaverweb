#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"

AsyncWebServer server(80);

const char* ssid = "212IntroRobotics";
const char* password = "robot2016";

float getVal() {
    // Function to retrieve data
    return random(1000) / 10.0; // Generate a random float between 0 and 100
}

void setup() {
    Serial.begin(115200);

    // Connect to WiFi
    WiFi.mode(WIFI_STA); 
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi. Local IP: ");
    Serial.println(WiFi.localIP());

    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("An error occurred while mounting SPIFFS");
        return;
    }

    // Route to serve the web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    // Route to serve data
    server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request) {
        // Generate data
        float value = getVal();
        
        // Prepare JSON response
        String json = "{\"time\": \"" + String(millis()) + "\", \"value\": " + String(value) + "}";
        
        // Send JSON response
        request->send(200, "application/json", json);
    });

    // Start server 
    server.begin();
}

void loop() {
    // Add your main code logic here
}
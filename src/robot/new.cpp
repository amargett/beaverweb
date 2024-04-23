#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include "imu.h"

AsyncWebServer server(80);

EulerAngles imuAngles; // IMU angles
EulerAngles imuGyro; // IMU angles from gyro

const char* ssid = "212IntroRobotics";
const char* password = "robot2016";

void getIMU() {
    EulerAngles newIMUAngles = readIMU();
    // only update PID if the IMU was read successfully
    if (!newIMUAngles.success){
        //if the IMU was not read successfully, print an error message and return
        Serial.println("IMU read failed");
    }
    // else Serial.println("IMU Read Success");
    //got an angle reading from the IMU
    if (!newIMUAngles.gyro){
        imuAngles = newIMUAngles;
    } else {
        //if the reading was from the gyro
        imuGyro = newIMUAngles;
    }
}

void setup() {
    Serial.begin(115200);

    imuSetup(); 
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

// Route to serve acceleration data
    server.on("/acceleration", HTTP_GET, [](AsyncWebServerRequest *request) {
        // Generate acceleration data (replace these with actual accelerometer readings)
        getIMU(); 
        float accelerationX = imuGyro.roll;
        float accelerationY = imuGyro.pitch;
        float accelerationZ = imuGyro.yaw;

        // Prepare JSON response
        String json = "{\"x\": " + String(accelerationX, 3) + ", \"y\": " + String(accelerationY, 3) + ", \"z\": " + String(accelerationZ, 3) + "}";

        // Send JSON response
        request->send(200, "application/json", json);
    });


    // Start server 
    server.begin();
}

void loop() {
}
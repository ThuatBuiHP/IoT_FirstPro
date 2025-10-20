#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "Tien Thuat";
const char* password = "07112004tien";
// URL of the web server
const char* url = "http://192.168.1.11:3000/";

void setup() {
  // put your setup code here, to run once:
  // Start a serial connection between the PC and the ESP32 at 9600 baud (UART)
  Serial.begin(9600);
  // Connect ESP32 to WiFi network with SSID and password
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print("..");
    delay(100);
  }
  Serial.println("WiFi connected");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED)
  {
    // Make ESP32 as HTTP client so it can send HTTP requests
    HTTPClient http;
    // Set up the connection between ESP32 and the web server
    http.begin(url);
    // Add the HTTP header to the request
    http.addHeader("Content-Type", "application/json");

    // Call API to receive data from the server
    String jsonData = "{\"tem\":\"20\"}";
    int res = http.POST(jsonData);
    if (res > 0) {
      Serial.println("POST request sent successfully");
      Serial.println(http.getString());
    }else{
      Serial.println("POST request failed");
      Serial.println(http.getString());
    }
    // After the client posts successfully, we end the connection
    http.end();
  }
  // Send the data to the server every 5 seconds
  delay(5000);
}
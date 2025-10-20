#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "Tien Thuat";
const char* password = "07112004tien";
const char* url = "http://192.168.1.11:3000/";

// The data pin on the DHT sensor is connected to GPIO pin 4 on the ESP32
#define DHTPIN 4
#define DHTTYPE DHT11

// Represents DHT11 sensor connected to GPIO pin 4
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  // Set up serial communication between your computer and ESP32 at 9600 baud
  Serial.begin(9600);
  // Connect ESP32 to your WiFi network
  WiFi.begin(ssid, password);
  // Initialize DHT sensor, prepare it for readings
  dht.begin();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("..");
    delay(500);
  }
  Serial.println("Connected ESP32 to WiFi");
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = 0;
  float hum = 0;
  // Read temperature and humidity from DHT sensor
  // If readings are valid, save them to variables
  if (dht.readTemperature() && dht.readHumidity())
  {
    temp = dht.readTemperature();
    hum = dht.readHumidity();
  }
  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(hum);
  
  // Send data to server by calling POST API
  if (WiFi.status() == WL_CONNECTED)
  {
    // Make ESP32 as a client
    HTTPClient http;
    // Start connection between ESP32 and server represented by URL
    http.begin(url);
    // Add extra information to the request, helping server to understand what data is being sent
    http.addHeader("Content-Type", "application/json");
    String jsonData = "{\"temperature\":" + String(temp) + ",\"humidity\":" + String(hum) + "}";
    int res = http.POST(jsonData);
    if (res > 0) {
      Serial.println("Data sent, response code: ");
      Serial.print(http.getString());
    }else{
      Serial.println("Error sending data");
      Serial.print(http.getString());
    }
    // Close connection between ESP32 and server, releasing resources
    http.end();
  }
  delay(5000);
}
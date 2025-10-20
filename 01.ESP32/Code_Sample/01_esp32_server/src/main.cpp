#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Set up your WiFi information
const char* ssid = "Tien Thuat";
const char* password = "07112004tien";
// Initialize the web server inside the ESP32
WebServer server(80);

void viewer() {
  String html = "<html><body>";
  html += "<a href='/on' style= 'font-size:40px;'> ON LED </a>";
  html += "<div>---------------------</div>";
  html += "<a href='/off' style= 'font-size:40px;'> OFF LED </a>";
  html += "</body></html>";
  // Send the HTML page to the client
  server.send(200, "text/html", html);
}

void turnOnLed() {
  digitalWrite(4, 1);
  Serial.println("LED ON");
}

void turnOffLed() {
  digitalWrite(4, 0);
  Serial.println("LED OFF");
}

void setup() {
  // put your setup code here, to run once:
  // Configure UART, set up or start a serial connection between the ESP32 and your computer
  // Set baud rate to 9600 to display the data in the serial monitor
  Serial.begin(9600);
  // Set up pin 4 as an output pin
  pinMode(4, OUTPUT);
  // Connect ESP32 to your wifi network
  WiFi.begin(ssid, password);
  // While the ESP32 is not connected to the WiFi network, it will display a message in the serial monitor
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("..");
    delay(100);
  }
  Serial.println("WiFi connected");
  // Print the IP address of the ESP32 to the serial monitor
  Serial.println(WiFi.localIP());

  // When opening the URL http://192.168.4.1/ in your browser, the ESP32 will run the viewer function
  server.on("/", viewer);
  server.on("/on", turnOnLed);
  server.on("/off", turnOffLed);
  // The server starts listening for incoming requests
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Check if there is a client connected to the ESP32 and handle the request
  server.handleClient();
}

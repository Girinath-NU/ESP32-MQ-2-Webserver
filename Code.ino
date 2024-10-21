#include <WiFi.h>

const char* ssid = "Device_Name";     // Replace with your network SSID
const char* password = "Password"; // Replace with your network password
WiFiServer server(80);  // Create a server that listens on port 80 (HTTP port)

int mq2pin = 33;  // Pin connected to MQ2 sensor

void setup() {
  // Start serial communication
  Serial.begin(9600);
  
  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  
  // Wait until Wi-Fi is connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  
  // Print the local IP address of the ESP32
  Serial.println("Connected to WiFi");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Start the server
  server.begin();
}

void loop() {
  // Read sensor value from MQ2 gas sensor
  int sensorvalue = analogRead(mq2pin);
  Serial.print("MQ2 Sensor Value: ");
  Serial.println(sensorvalue);
  delay(1000);

  // Check if a client has connected
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("New Client Connected");

    // Wait until the client sends data
    while (!client.available()) {
      delay(1);
    }

    // Read the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    
    // Send HTTP response header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();  // End of HTTP header

    // Create and send the HTML content
    client.println("<!DOCTYPE html><html>");
    client.println("<head><title>ESP32 Web Server</title></head>");
    client.println("<body><h1>ESP32 Web Server</h1>");
    
    // Display the current MQ2 sensor value
    client.println("<p>MQ2 Sensor Value: " + String(sensorvalue) + "</p>");
    
    client.println("</body></html>");

    // Close the connection
    client.stop();
    Serial.println("Client Disconnected");
  }
}

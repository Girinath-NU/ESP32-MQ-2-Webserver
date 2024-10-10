# ESP32 Web Server with MQ2 Gas Sensor

This project uses an **ESP32** microcontroller to read data from an **MQ2 gas sensor** and display the values on a web page served by the ESP32. The web server updates the MQ2 sensor readings every time a new client connects to the server.

## Components Used
- **ESP32**: The microcontroller handling Wi-Fi and sensor communication.
- **MQ2 Gas Sensor**: A sensor used to detect gas concentrations (smoke, LPG, etc.).
- **Wi-Fi Network**: The ESP32 connects to a Wi-Fi network to serve the webpage.
  
## Features
- Connects the ESP32 to a Wi-Fi network.
- Reads analog values from the MQ2 sensor (connected to pin 33).
- Hosts a web server on port 80.
- Displays the current gas sensor readings on a web page.

## Prerequisites
- ESP32 microcontroller.
- MQ2 gas sensor connected to an analog pin (pin 33 in this case).
- Wi-Fi network (SSID and password required).
- Arduino IDE with ESP32 board support installed.

## Setup and Usage

1. **Hardware Connections**:
    - Connect the **analog output** of the MQ2 sensor to **pin 33** of the ESP32.
    - Connect the VCC and GND of the MQ2 sensor to 3.3V and GND on the ESP32.

2. **Software Configuration**:
    - Install the **ESP32 board** in the Arduino IDE by adding the following URL in the preferences section:
      ```
      https://dl.espressif.com/dl/package_esp32_index.json
      ```
    - In the Arduino IDE, go to `Tools` > `Board` and select **ESP32 Dev Module**.

3. **Wi-Fi Credentials**:
    - Replace the following lines in the code with your own Wi-Fi SSID and password:
      ```cpp
      const char* ssid = "your_SSID";     // Replace with your network SSID
      const char* password = "your_PASSWORD"; // Replace with your network password
      ```

4. **Upload Code**:
    - Upload the provided code to your ESP32 using the Arduino IDE.

5. **Access the Web Server**:
    - After the ESP32 connects to Wi-Fi, it will print its IP address in the serial monitor.
    - Open a web browser and enter the ESP32's IP address in the URL bar to access the webpage displaying the MQ2 sensor value.

## Code Overview

### Wi-Fi Connection
The code connects to a Wi-Fi network using the `WiFi.begin()` function. It continues trying to connect until successful, and then it prints the ESP32's IP address.

```cpp
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.println("Connecting...");
}
Serial.println("Connected to WiFi");

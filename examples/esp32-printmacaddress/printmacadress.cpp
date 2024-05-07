#include "WiFi.h"

void setup() {
  Serial.begin(115200);  // Start the Serial communication to send messages to the computer
  delay(10);
}

void loop() {
  Serial.println("\nESP32 MAC Address:");

  // Get the Wi-Fi MAC address of the ESP32
  uint8_t macAddr[6];  // Array to hold the MAC address
  WiFi.macAddress(macAddr);
  
  // Print the MAC address in human-readable format
  Serial.print("MAC Address: ");
  for (int i = 0; i < 5; i++) {
    Serial.printf("%02X:", macAddr[i]);
  }
  Serial.printf("%02X", macAddr[5]);

    delay(2000);
}

#include <Arduino.h>
#include <WiFiManager.h> // install from PlatformIO lib_deps

WiFiManager wm;

void setup()
{
  Serial.begin(115200);

  // Start AP if no saved Wi-Fi, otherwise connect
  // IP address: 192.168.4.1
  if (!wm.autoConnect("ESP32-Setup", "12345678"))
  {
    Serial.println("Failed to connect, running AP mode");
  }
  else
  {
    Serial.println("Connected to Wi-Fi!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  }
}

void loop()
{
  // This keeps the configuration portal running
  wm.process();
}

#include <Arduino.h>
#include <WiFiManager.h>
#include <HTTPClient.h>

// ================== WiFi Module ==================
class WiFiModule
{
public:
  WiFiManager wm;

  void init()
  {
    Serial.begin(115200);

    // Start AP if no saved Wi-Fi, otherwise connect
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

  void update()
  {
    // Keep WiFiManager portal alive
    wm.process();
  }
};

// ================== Discord Module ==================
class DiscordModule
{
public:
  bool messageSent = false; // flag to send only once

  void init()
  {
    // nothing special here, could preload config later
  }

  void update()
  {
    if (WiFi.status() == WL_CONNECTED && !messageSent)
    {
      sendMessage("ESP32 is online and connected!");
      messageSent = true; // prevent re-sending
    }
  }

private:
  void sendMessage(const String &content)
  {
    HTTPClient http;
    String webhook_url = "https://discord.com/api/webhooks/1417920471592079360/q2cZ47f8lfYEjiucKH9maS7IBV57DyHPLhPrnY0CQJxxK_ZIqmne98x20Lg9zGgA41tY";

    http.begin(webhook_url);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"content\":\"" + content + "\"}";
    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0)
    {
      Serial.print("Message sent, code: ");
      Serial.println(httpResponseCode);
    }
    else
    {
      Serial.print("Error: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }

    http.end();
  }
};

// ================== Main Program ==================
WiFiModule wifi;
DiscordModule discord;

void setup()
{
  wifi.init();
  discord.init();
}

void loop()
{
  wifi.update();
  discord.update();
}

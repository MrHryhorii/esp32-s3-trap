#include <Arduino.h>

int ledPin = 2; // found onboard LED pin

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, HIGH);
  Serial.println("LED ON");
  delay(1000);

  digitalWrite(ledPin, LOW);
  Serial.println("LED OFF");
  delay(1000);
}

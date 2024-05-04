#include <ESP8266WiFi.h>
#include "env.h"

bool is_led_on;
unsigned long timer;

void setup() {
  pinMode(D5, OUTPUT); // wifi connection status led

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    yield();
  }

  digitalWrite(D5, HIGH);
  is_led_on = true;
  timer = millis();
}

void loop() {

  if(millis() - timer >= 5000UL) {
      timer = millis();
      if (is_led_on)
        digitalWrite(D5, LOW);
      else
        digitalWrite(D5, HIGH);
      is_led_on = !is_led_on;
  }
}

#include <ESP8266WiFi.h>
#include "env.h"
#include "wifi.h"

bool is_led_on;
unsigned long timer;

void setup() {
  pinMode(D5, OUTPUT); // wifi connection status led
  pinMode(D6, OUTPUT);
  connect_to_wifi(ssid, password);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, OUTPUT);
  is_led_on = true;
  timer = millis();
}

void loop() {

  if(millis() - timer >= 2000UL) {
      timer = millis();
      if (is_led_on)
        digitalWrite(D6, LOW);
      else
        digitalWrite(D6, HIGH);
      is_led_on = !is_led_on;
  }
}

#include <ESP8266WiFi.h>
#include "wifi.h"

void connect_to_wifi(const char* ssid, const char* password) {

  WiFi.begin(ssid, password);
  unsigned long timer = millis();
  bool is_led_on = true;
  digitalWrite(D5, HIGH);
  
  while (WiFi.status() != WL_CONNECTED) {
    if(millis() - timer >= 250UL) {
      timer = millis();
      if (is_led_on)
        digitalWrite(D5, LOW);
      else
        digitalWrite(D5, HIGH);
      is_led_on = !is_led_on;
    }
    yield();
  }
}
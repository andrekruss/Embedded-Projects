#define LED_PIN 2
#define INTERVAL 2000UL

unsigned long timer;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    timer = millis();
}

void loop() {

    if (millis() - timer >= INTERVAL){
        timer = millis();
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
}
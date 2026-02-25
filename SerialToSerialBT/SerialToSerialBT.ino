#include "BluetoothSerial.h"
#include <Arduino.h>

BluetoothSerial hi;
#define LED 2
#define BUZZER 5

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(LED, LOW);
  ledcAttach(BUZZER, 400, 8);

  hi.begin(115200);
  hi.setTimeout(50);
}

void loop() {
  if (hi.available()) {
    String s = hi.readString();

    if (s == "ON") {
      digitalWrite(LED, HIGH);
      ledcWrite(BUZZER, 200);
      hi.println("fdgsahjko");
    } else if (s == "OFF") {
      digitalWrite(LED, LOW);
      ledcWrite(BUZZER, 0);
      hi.println("kjhgf");
    }    
  }
}

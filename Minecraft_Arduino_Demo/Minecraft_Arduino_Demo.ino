#include "MCreatorLink.h"

const int buzzer = 10;

const int red = 3;
const int green = 5;
const int blue = 6;

void dataEvent(String command, String data) {
  if (data.equals("w")) {
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
  }
  else if(data.equals("r")) {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
  }
  else if (data.equals("g")) {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
  }
  else if (data.equals("b")) {
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, HIGH);
  }
  else if (data.equals("c")) {
    //Clear
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
  }
  else if (data.equals("buzz")) {
    analogWrite(buzzer, 100);
    delay(500);
    digitalWrite(buzzer, LOW);
  }
}

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);

  Serial.begin(115200);
  Serial.setTimeout(20);
  MCreatorLink.setup(Serial, "Device Name");
  MCreatorLink.setListener(dataEvent);
}

void loop() {
    MCreatorLink.loop();
}

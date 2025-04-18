#include "MCreatorLink.h"

const int count = 5;
const int offset = 0;

void dataEvent(String command, String data) {

  int value1 = command.substring(0, 3).toInt();
  int value2 = command.substring(3, 6).toInt();
  int ledsOn = map(value1, 0, 255, 0, count);
  
  //clear
  for (int i = 2 + offset; i < count + 2 + offset; i++)
  {
    digitalWrite(i, LOW);
  }
  digitalWrite(A5, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A0, LOW);

  for (int i = count + 1; i > count - ledsOn + 1; i--)
  {
    digitalWrite(i, HIGH);
  }
  if (ledsOn >= 13 - count) { digitalWrite(A0, HIGH); }
  if (ledsOn >= 14 - count) { digitalWrite(A1, HIGH); }
  if (ledsOn >= 15 - count) { digitalWrite(A2, HIGH); }
  if (ledsOn >= 16 - count) { digitalWrite(A3, HIGH); }
  if (ledsOn >= 17 - count) { digitalWrite(A4, HIGH); }
  if (ledsOn >= 18 - count) { digitalWrite(A5, HIGH); }
  
  if (value2 > 0)
    analogWrite(3, value2);
}

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(20);
    MCreatorLink.setup(Serial, "Device Name");
    MCreatorLink.setListener(dataEvent);

    for(int i = 2; i < count + 2; i++)
    {
      if (i <= 13) { pinMode(i, OUTPUT); }
    }
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
}

void loop() {
    MCreatorLink.loop();
}
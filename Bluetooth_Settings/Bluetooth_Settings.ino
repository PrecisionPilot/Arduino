#include <SoftwareSerial.h>
SoftwareSerial Bserial(10, 11);
String b = "";
void setup() {
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  Bserial.begin(38400);  // HC-05 default speed in AT command more
}

void loop() {
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (Bserial.available())
    Serial.write(Bserial.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    Bserial.write(Serial.read());
}

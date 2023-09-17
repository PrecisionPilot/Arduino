#include <NewPing.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     13
#define MAX_DISTANCE 500

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int cm;

void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  delay(50);
  unsigned int uS = sonar.ping();
  //Serial.print("Ping: ");
  cm = uS / US_ROUNDTRIP_CM;
  Serial.print(cm);
  Serial.println("cm");
}

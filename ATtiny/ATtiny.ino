void setup() {
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
}

void loop() {
  digitalWrite(1, HIGH);
  delay(100);
  digitalWrite(1, LOW);
  delay(100);
}

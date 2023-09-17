void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(5);
}

void loop() {
  Serial.println(digitalRead(19));
}

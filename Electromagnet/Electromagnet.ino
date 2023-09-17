void setup() {
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() {
  while (!Serial.available()){}
  String x = Serial.readString();
  if (x == "1"){
    digitalWrite(2, HIGH);
    digitalWrite(13, HIGH);
  }
  else if (x == "0"){
    digitalWrite(2, LOW);
    digitalWrite(13, LOW);
  }

//  digitalWrite(2, HIGH);
//  digitalWrite(3, HIGH);
//
//  delay(500);
//
//  digitalWrite(2, LOW);
//  digitalWrite(3, LOW);
//
//  delay(500);
}

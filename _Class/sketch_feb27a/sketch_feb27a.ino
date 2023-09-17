void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.begin(1000000);
  Serial.setTimeout(8);
}

void loop()
{
  while(Serial.available() == false){}
  String s = Serial.readString();
  
  s.substring(0, 3);
  int x = s.toInt();
  x = map(x, 0, 255, 0, 6);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  
  if(x >= 1){
    digitalWrite(2, HIGH);
  }
  if(x >= 2){
    digitalWrite(3, HIGH);
  }
  if(x >= 3){
    digitalWrite(4, HIGH);
  }
  if(x >= 4){
    digitalWrite(5, HIGH);
  }
  if(x >= 5){
    digitalWrite(6, HIGH);
  }
  if(x >= 6){
    digitalWrite(7, HIGH);
  }

  
}

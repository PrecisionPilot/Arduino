void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  Serial.begin(9600);
  Serial.setTimeout(50);
}

void loop()
{
  while(Serial.available() == false){}
  int x = Serial.readString().toInt();
  
  if(x >= 1){
    digitalWrite(2, HIGH);
  }
  else{
    digitalWrite(2, LOW);
  }
  
  if(x >= 2){
    digitalWrite(3, HIGH);
  }
  else{
    digitalWrite(3, LOW);
  }
  
  if(x >= 3){
    digitalWrite(4, HIGH);
  }
  else{
    digitalWrite(4, LOW);
  }
  
  if(x >= 4){
    digitalWrite(5, HIGH);
  }
  else{
    digitalWrite(5, LOW);
  }
  
  if(x >= 5){
    digitalWrite(6, HIGH);
  }
  else{
    digitalWrite(6, LOW);
  }
  
  if(x >= 6){
    digitalWrite(7, HIGH);
  }
  else{
    digitalWrite(7, LOW);
  }
  
}

void setup() {
  pinMode(3, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
  Serial.setTimeout(50);
}

void loop() {
  while(Serial.available() == false){}
  int x = Serial.readString().toInt();

  if(x == 6){
    digitalWrite(8, HIGH);
  }
  else{
    digitalWrite(8, LOW);
  }
  
  if(x == 5){
    digitalWrite(9, HIGH);
  }
  else{
    digitalWrite(9, LOW);
  }
  
  if(x == 4){
    digitalWrite(10, HIGH);
  }
  else{
    digitalWrite(10, LOW);
  }
  
  if(x == 3){
    digitalWrite(11, HIGH);
  }
  else{
    digitalWrite(11, LOW);
  }
  
  if(x == 2){
    digitalWrite(12, HIGH);
  }
  else{
    digitalWrite(12, LOW);
  }
  
  if(x == 1){
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }
}

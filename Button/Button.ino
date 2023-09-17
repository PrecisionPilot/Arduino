bool state = false;
bool pressed = false;

void setup() {
  pinMode(8, INPUT);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  Serial.setTimeout(50);
}

void loop() {
  if (digitalRead(8) && !pressed){
    state = !state;
    pressed = true;
  }
  else if (!digitalRead(8) && pressed){
    pressed = false;
  }

  if(state){
    digitalWrite(2, HIGH);
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(2, LOW);
    digitalWrite(13, LOW);
  }
}

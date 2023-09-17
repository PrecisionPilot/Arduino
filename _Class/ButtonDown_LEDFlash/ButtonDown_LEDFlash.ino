bool buttonState;
bool state;
bool LEDState;

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(3, INPUT);

  Serial.begin(9600);
  Serial.setTimeout(50);
}

void loop() {
  if(digitalRead(3) && !buttonState){
    LEDState = !LEDState;
    if(LEDState){
      digitalWrite(8, HIGH);
    }
    else{
      digitalWrite(8, LOW);
    }
    buttonState = true;
  }
  if(!digitalRead(3) && buttonState){
    buttonState = false;
  }
}    

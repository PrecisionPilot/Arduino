unsigned long t1;
unsigned long t2;
unsigned long t3;

bool LED1;
bool LED2;
bool LED3;

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(3, INPUT);

  Serial.begin(9600);
  Serial.setTimeout(50);
}

void loop() {
  if(millis() >= t1 + 500){
    LED1 = !LED1;
    if(LED1){
      digitalWrite(8, HIGH);
    }
    else{
      digitalWrite(8, LOW);
    }
    t1 = millis();
  }

  if(millis() >= t2 + 750){
    LED2 = !LED2;
    if(LED2){
      digitalWrite(9, HIGH);
    }
    else{
      digitalWrite(9, LOW);
    }
    t2 = millis();
  }

  if(millis() >= t3 + 1100){
    LED3 = !LED3;
    if(LED3){
      digitalWrite(10, HIGH);
    }
    else{
      digitalWrite(10, LOW);
    }
    t3 = millis();
  }
}    

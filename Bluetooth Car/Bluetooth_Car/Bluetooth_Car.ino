int groundSpeed = 255;

#define MOTORL1 18
#define MOTORL2 19
#define MOTORR1 21
#define MOTORR2 22
#define LED 2

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);

  pinMode(MOTORL1, OUTPUT);
  pinMode(MOTORL2, OUTPUT);
  pinMode(MOTORR1, OUTPUT);
  pinMode(MOTORR2, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  char output = Serial.read();//store the serial signal comming from the bluetooth serial port as a character variable
  int outputInt = (char)output;
  //set goundspeed
  for(int i = 0; i < 10; i++)
  {
    if((String)output == (String)i)
    {
      groundSpeed = map(i, 0, 10, 0, 255);
    }
  }
  if(output == 'S')//Standby Mode
  {
    analogWrite(MOTORL1, 0);//the same as digitalWrite(MOTORL1, LOW);
    analogWrite(MOTORL2, 0);
    analogWrite(MOTORR1, 0);
    analogWrite(MOTORR2, 0);
  }
  else if(output == 'D')//Disconnected
  {
    analogWrite(MOTORL1, 0);
    analogWrite(MOTORL2, 0);
    analogWrite(MOTORR1, 0);
    analogWrite(MOTORR2, 0);
    return;
  }
  else if(output == 'q')//Full Speed
  {
    groundSpeed = 255; //the same as: map(10, 0, 10, 0, 255);
  }
  else if(output == 'F')//Forward
  {
    analogWrite(MOTORL1, groundSpeed);
    analogWrite(MOTORL2, 0);
    analogWrite(MOTORR1, groundSpeed);
    analogWrite(MOTORR2, 0);

    delay(2000);

    analogWrite(MOTORL1, 0);
    analogWrite(MOTORR1, 0);
  }
  else if(output == 'B')//Backwards
  {
    analogWrite(MOTORL1, 0);
    analogWrite(MOTORL2, groundSpeed);
    analogWrite(MOTORR1, 0);
    analogWrite(MOTORR2, groundSpeed);

    delay(2000);

    analogWrite(MOTORL2, 0);
    analogWrite(MOTORR2, 0);
  }
  else if(output == 'L')//Turn Left
  {
    analogWrite(MOTORL1, 0);
    analogWrite(MOTORL2, 0);
    analogWrite(MOTORR1, groundSpeed);
    analogWrite(MOTORR2, 0);
  }
  else if(output == 'R')//Turn Right
  {
    analogWrite(MOTORL1, groundSpeed);
    analogWrite(MOTORL2, 0);
    analogWrite(MOTORR1, 0);
    analogWrite(MOTORR2, 0);
  }
  else if(output == 'G')//Forward Turning Left
  {
    analogWrite(MOTORL1, groundSpeed / 4);
    analogWrite(MOTORL2, 0);
    analogWrite(MOTORR1, groundSpeed);
    analogWrite(MOTORR2, 0);
  }
  else if(output == 'I')//Forward Turning Right
  {
    analogWrite(MOTORL1, groundSpeed);
    analogWrite(MOTORL2, 0);
    analogWrite(MOTORR1, groundSpeed / 4);
    analogWrite(MOTORR2, 0);
  }
  else if(output == 'H')//Backward Turning Left
  {
    analogWrite(MOTORL1, 0);
    analogWrite(MOTORL2, groundSpeed / 4);
    analogWrite(MOTORR1, 0);
    analogWrite(MOTORR2, groundSpeed);
  }
  else if(output == 'J')//Backward Turning Right
  {
    analogWrite(MOTORL1, 0);
    analogWrite(MOTORL2, groundSpeed);
    analogWrite(MOTORR1, 0);
    analogWrite(MOTORR2, groundSpeed / 4);
  }
  //Horn Control
  else if(output == 'V')
  {
    analogWrite(11, 10);
  }
  else if(output == 'v')
  {
    digitalWrite(11, LOW);
  }
  
  //Light Control
  else if(output == 'W')
  {digitalWrite(LED, HIGH);}
  else if(output == 'w')
  {digitalWrite(LED, LOW);}
  
  while(Serial.available() == 0){/*Do nothing while the bluetooth serial port isn't sending any data*/}
}

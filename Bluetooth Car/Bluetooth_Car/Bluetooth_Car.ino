int groundSpeed = 255;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);

  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
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
    analogWrite(3, 0);//the same as digitalWrite(3, LOW);
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
  }
  else if(output == 'D')//Disconnected
  {
    analogWrite(3, 0);
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
    return;
  }
  else if(output == 'q')//Full Speed
  {
    groundSpeed = 255; //the same as: map(10, 0, 10, 0, 255);
  }
  else if(output == 'F')//Forward
  {
    analogWrite(3, groundSpeed);
    analogWrite(5, 0);
    analogWrite(6, groundSpeed);
    analogWrite(9, 0);
  }
  else if(output == 'B')//Backwards
  {
    analogWrite(3, 0);
    analogWrite(5, groundSpeed);
    analogWrite(6, 0);
    analogWrite(9, groundSpeed);
  }
  else if(output == 'L')//Turn Left
  {
    analogWrite(3, 0);
    analogWrite(5, 0);
    analogWrite(6, groundSpeed);
    analogWrite(9, 0);
  }
  else if(output == 'R')//Turn Right
  {
    analogWrite(3, groundSpeed);
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
  }
  else if(output == 'G')//Forward Turning Left
  {
    analogWrite(3, groundSpeed / 4);
    analogWrite(5, 0);
    analogWrite(6, groundSpeed);
    analogWrite(9, 0);
  }
  else if(output == 'I')//Forward Turning Right
  {
    analogWrite(3, groundSpeed);
    analogWrite(5, 0);
    analogWrite(6, groundSpeed / 4);
    analogWrite(9, 0);
  }
  else if(output == 'H')//Backward Turning Left
  {
    analogWrite(3, 0);
    analogWrite(5, groundSpeed / 4);
    analogWrite(6, 0);
    analogWrite(9, groundSpeed);
  }
  else if(output == 'J')//Backward Turning Right
  {
    analogWrite(3, 0);
    analogWrite(5, groundSpeed);
    analogWrite(6, 0);
    analogWrite(9, groundSpeed / 4);
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
  {digitalWrite(13, HIGH);}
  else if(output == 'w')
  {digitalWrite(13, LOW);}
  
  while(Serial.available() == 0){/*Do nothing while the bluetooth serial port isn't sending any data*/}
}

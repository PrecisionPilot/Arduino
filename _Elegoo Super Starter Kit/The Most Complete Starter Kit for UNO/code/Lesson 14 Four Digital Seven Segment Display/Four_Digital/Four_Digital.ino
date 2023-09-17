//www.elegoo.com
//2016.06.13

int latchPin = 8;
int clockPin = 12;
int dataPin = 11; //define three kinds of pin
void setup ()
{
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT); //set the three pins as output
}
void loop()
{

  int a[10]={
    3,159,37,13,153,73,65,27,1,9  };   //Define array functions, define an array of digital tube
  for(int x=9; x>-1 ;x-- )                        // Inverse function cycle
  {
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,a[x]);     //show array a[x]
    digitalWrite(latchPin,HIGH);
    delay(1000);
  }
}


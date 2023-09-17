//www.elegoo.com
//2016.06.13

int x, y, z;
int a1 = A0;
int a2 = A1;
int a3 = A2;
void setup()
{
  pinMode(a1,INPUT);
  pinMode(a2,INPUT);
  pinMode(a3,INPUT);
  Serial.begin(9600);   
}
void loop()
{
  x = analogRead(a1);     
  y = analogRead(a2);     
  z = analogRead(a3);     
  Serial.print("x:  ");
  Serial.print(x, DEC);  
  Serial.print(" "); 
 Serial.print("y:  "); 
  Serial.print(y, DEC);   
  Serial.print(" "); 
 Serial.print("z:  "); 
  Serial.println(z, DEC); 
  delay(100);            
}

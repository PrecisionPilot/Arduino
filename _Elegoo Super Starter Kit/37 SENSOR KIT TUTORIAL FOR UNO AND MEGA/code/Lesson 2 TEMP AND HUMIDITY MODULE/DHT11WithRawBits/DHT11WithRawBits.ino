#include <SimpleDHT.h>

int pinDHT11 = A0;
SimpleDHT11 dht11;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // start working...
  Serial.println("=================================");//seperator
  
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) { // if fails to read data
    Serial.print("Read DHT11 failed");//error message
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" %");
  
  if (temperature >= 27)
  { digitalWrite(2, HIGH);}
  else
  { digitalWrite(2, LOW);}

  if (temperature >= 28)
  { digitalWrite(3, HIGH);}
  else
  {digitalWrite(3, LOW);}

  if (temperature >= 29)
  { digitalWrite(4, HIGH);}
  else
  {digitalWrite(4, LOW);}
  
  // DHT11 sampling rate is 1HZ.
  delay(500);
}

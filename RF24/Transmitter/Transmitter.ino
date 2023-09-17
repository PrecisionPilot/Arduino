/*#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <SPI.h>

RF24 radio(7, 8); //CNS, CE

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  if(Serial.available())
  {
    char text[32] = { 0 };
    Serial.readString().toCharArray(text, 32);
    radio.write(&text, sizeof(text));
  }
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(1000);
}*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(1000);
}

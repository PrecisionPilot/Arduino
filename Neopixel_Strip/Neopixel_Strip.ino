#include <Adafruit_NeoPixel.h>

const int stripCount = 60;
const int stripPin = 8;
const int pot = A5;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(stripCount, stripPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.clear();
  strip.show();
  
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() {
//  while (!Serial.available()){}
//  strip.clear();
//  String x = Serial.readString();
//
//  if (x == "red"){
//    strip.clear();
//    for (int i = 0; i < stripCount; i++){
//      strip.setPixelColor(i, 255, 0, 0);
//      delay(50);
//      strip.show();
//    }
//  }
//  else if (x == "green"){
//    strip.clear();
//    for (int i = 0; i < stripCount; i++){
//      strip.setPixelColor(i, 0, 255, 0);
//      delay(50);
//      strip.show();
//    }
//  }
//  else if (x == "blue"){
//    strip.clear();
//    for (int i = 0; i < stripCount; i++){
//      strip.setPixelColor(i, 0, 0, 255);
//      delay(50);
//      strip.show();
//    }
//  }
//  else if (x == "rainbow"){
//    for (int i = 0; i < 3000; i++){
//      forEachPixel(i, i, i);
//      delay(16.7);
//    }
//  }
//  else{
//    for (int i = 0; i < x.toInt(); i++){
//      strip.setPixelColor(i, 255, 255, 255);
//    }
//    strip.show();
//  }  
  strip.clear();
  for (int i = 0; i < map(analogRead(pot), 0, 1023, 0, stripCount); i++){
    strip.setPixelColor(i, 255, 255, 255);
  }
  strip.show();
}

void forEachPixel(int red, int green, int blue){
  for (int i = 0; i < stripCount; i++){
    strip.setPixelColor(i, red, green, blue);
  }
  strip.show();

  
}

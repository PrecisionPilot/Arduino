#include <Adafruit_NeoPixel.h>

const int trigPin = 12;
const int echoPin = 13;
const int pin = 3;
const int numPixels = 150;

long duration;
int distance;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, pin, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);

  strip.setBrightness(255);
  strip.begin();
  Serial.begin(9600);
  Serial.setTimeout(50);
}
void loop() {
  
  // Prints the distance on the Serial Monitor
  // Serial.print("Distance: ");
  // distance = getDistance();
  // Serial.println(distance);

  // strip.clear();
  // for (int i = 0; i < distance / 4; i++) {
  //   strip.setPixelColor(i, strip.Color(0, 255, 128));
  // }
  // strip.show();

  while (!Serial.available()) {}

  String userInput = Serial.readString();
  int value1 = userInput.substring(0, 3).toInt();
  int value2 = userInput.substring(3, 6).toInt();

  // Light up n LEDs
  // int n = map(value1, 0, 255, 0, 100);
  int n = value1;
  strip.clear();
  for (int i = 0; i < n; i++) {
    // strip.setPixelColor(i, strip.Color(255, 255, 255));
    // Red
    if (i % 3 == 0) {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    // Green
    else if (i % 3 == 1) {
      strip.setPixelColor(i, strip.Color(0, 255, 0));
    }
    // Blue
    else {
      strip.setPixelColor(i, strip.Color(0, 250, 255));
    }
  }
  strip.show();

  // for (int i = 0; i < numPixels; i++) {
  //   strip.setPixelColor(i, strip.Color(255, 255, 255)); // Moderately bright green color.
  //   strip.show(); // This sends the updated pixel color to the hardware.
  //   Serial.println(i);
  //   delay(100); // Delay for a period of time (in milliseconds).
  // }
  // for (int i = numPixels - 1; i >= 0; i--) {
  //   strip.setPixelColor(i, strip.Color(0, 0, 0));
  //   strip.show();
  //   delay(100);
  // }
}

int getDistance() {
// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  return distance;
}
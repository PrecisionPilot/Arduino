#include <FastLED.h>

#define DATA_PIN A0
#define NUM_LEDS 9

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(255, 255, 255);
    
    FastLED.show();
  }
}

void loop() {

}

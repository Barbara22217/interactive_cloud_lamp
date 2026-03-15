#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    60
#define BRIGHTNESS  80
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

 
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 3 == 0) {
      leds[i] = CRGB(255, 100, 100);   // soft red/pink
    } 
    else if (i % 3 == 1) {
      leds[i] = CRGB(100, 100, 255);   // soft blue
    } 
    else {
      leds[i] = CRGB(100, 255, 150);   // soft green
    }
  }

  FastLED.show();
}

void loop() {
}

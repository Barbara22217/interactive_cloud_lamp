#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    60
#define BRIGHTNESS  80
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

#define BUTTON_PIN  2

CRGB leds[NUM_LEDS];
bool ledOn = true;   

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(BUTTON_PIN, INPUT_PULLUP); // button setup

  // start with LEDs ON
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(180, 180, 255); // cloud color
  }
  FastLED.show();
}

void loop() {
  static bool lastButtonState = HIGH;
  bool currentButtonState = digitalRead(BUTTON_PIN);

  
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    ledOn = !ledOn;   
  }

  lastButtonState = currentButtonState;

  if (ledOn) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(180, 180, 255);
    }
  } else {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
  delay(20); 
}

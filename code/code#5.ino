#include <FastLED.h>

#define LED_PIN 3
#define NUM_LEDS 60
#define BUTTON_PIN 2
#define POT_PIN A0

CRGB leds[NUM_LEDS];
bool ledOn = true;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(BUTTON_PIN, INPUT_PULLUP);   

void loop() {
  // ---- BUTTON ----
  static bool lastButtonState = HIGH;
  bool buttonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && buttonState == LOW) {
    ledOn = !ledOn;
    delay(200); 
  }
  lastButtonState = buttonState;

  // ---- POTENTIOMETER ----
  int potValue = analogRead(POT_PIN);
  int brightness = map(potValue, 0, 1023, 0, 150);

  if (ledOn) {
    FastLED.setBrightness(brightness);
    fill_solid(leds, NUM_LEDS, CRGB::Blue); // cloud color
  } else {
    FastLED.clear();
  }

  FastLED.show();
}

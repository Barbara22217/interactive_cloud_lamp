#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    60
#define BUTTON_PIN  2
#define POT_PIN     A0

CRGB leds[NUM_LEDS];

// Lamp state
bool ledOn = true;
int colorMode = 0;
bool breathingOn = true;

// Button timing
unsigned long buttonPressTime = 0;
bool buttonHeld = false;

// Breathing/fade variables
float brightnessLevel = 0;
float fadeDirection = 1;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  // ---------- BUTTON ----------
  if (buttonState == LOW && !buttonHeld) {
    buttonPressTime = millis();
    buttonHeld = true;
  }

  if (buttonState == HIGH && buttonHeld) {
    unsigned long pressDuration = millis() - buttonPressTime;

    if (pressDuration < 800) {
      // SHORT PRESS → ON/OFF
      ledOn = !ledOn;
    } else {
      // LONG PRESS → CHANGE COLOR
      colorMode = (colorMode + 1) % 3;
    }

    buttonHeld = false;
    delay(150); 
  }

  // ---------- POTENTIOMETER ----------
  int potValue = analogRead(POT_PIN);
  int maxBrightness = map(potValue, 0, 1023, 0, 150);

  if (potValue < 50) {
    breathingOn = false;
    FastLED.setBrightness(maxBrightness);
  } else {
    breathingOn = true;
  }

  // ---------- BREATHING EFFECT ----------
  if (ledOn) {
if (breathingOn) {
  brightnessLevel += fadeDirection * 0.3; 
  if (brightnessLevel >= maxBrightness) fadeDirection = -1;
  if (brightnessLevel <= 1) fadeDirection = 1; 
  FastLED.setBrightness((int)brightnessLevel);
} else {
  FastLED.setBrightness(maxBrightness); 
    // ---------- SET COLOR ----------
    if (colorMode == 0) fill_solid(leds, NUM_LEDS, CRGB::Blue);
    else if (colorMode == 1) fill_solid(leds, NUM_LEDS, CRGB::Purple);
    else if (colorMode == 2) fill_solid(leds, NUM_LEDS, CRGB(255, 180, 120));
  } else {
    FastLED.clear();
  }

  FastLED.show();
  delay(20);
}

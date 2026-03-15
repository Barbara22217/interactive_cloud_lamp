#include <FastLED.h>

#define LED_PIN 3
#define NUM_LEDS 60
#define BUTTON_PIN 2
#define POT_PIN A0

CRGB leds[NUM_LEDS];

bool ledOn = true;
int colorMode = 0;

unsigned long buttonPressTime = 0;
bool buttonHeld = false;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // ---- READ BUTTON ----
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && !buttonHeld) {
    buttonPressTime = millis();
    buttonHeld = true;
  }

  if (buttonState == HIGH && buttonHeld) {
    unsigned long pressDuration = millis() - buttonPressTime;

    if (pressDuration < 800) {
      // SHORT PRESS → ON / OFF
      ledOn = !ledOn;
    } else {
      // LONG PRESS → CHANGE COLOR
      colorMode = (colorMode + 1) % 3;
    }

    buttonHeld = false;
    delay(200); 
  }

  // ---- POTENTIOMETER = BRIGHTNESS ----
  int potValue = analogRead(POT_PIN);
  int brightness = map(potValue, 0, 1023, 0, 150);
  FastLED.setBrightness(brightness);

  // ---- LED OUTPUT ----
  if (ledOn) {
    if (colorMode == 0) {
      fill_solid(leds, NUM_LEDS, CRGB::Blue);
    }
    else if (colorMode == 1) {
      fill_solid(leds, NUM_LEDS, CRGB::Purple);
    }
    else if (colorMode == 2) {
    fill_solid(leds, NUM_LEDS, CRGB(255, 180, 120)); // 
}    }
  } else {
    FastLED.clear();
  }

  FastLED.show();
}

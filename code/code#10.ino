#include <FastLED.h>

#define LED_PIN 3
#define NUM_LEDS 60
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

// Pins
const int button1 = 6;
const int button2 = 2;
const int potPin = A0;

// Lamp states
bool lampOn = true;
bool partyMode = false;

int colorIndex = 0;

// button variables
unsigned long pressStart = 0;
bool buttonActive = false;
bool longPressTriggered = false;

// button 2
bool lastButton2 = HIGH;

// colors
CRGB colors[] = {
  CRGB::Blue,
  CRGB::HotPink,
  CRGB::White
};

void setup() {

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
 

  FastLED.clear();
  FastLED.show();
}

void partyEffect() {

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(random8(), 255, 255);
  }
}

void handleButton1(){

  bool btn = digitalRead(button1);

  if (btn == LOW && !buttonActive) {
    buttonActive = true;
    longPressTriggered = false;
    pressStart = millis();
  }

  if (btn == LOW && buttonActive && !longPressTriggered) {

    if (millis() - pressStart > 700) {

      colorIndex++;

      if (colorIndex > 2)
        colorIndex = 0;

      longPressTriggered = true;
    }
  }

  if (btn == HIGH && buttonActive) {

    if (!longPressTriggered) {
      lampOn = !lampOn;
    }

    buttonActive = false;
  }
}

void handleButton2(){

  bool current = digitalRead(button2);

  if (lastButton2 == HIGH && current == LOW) {
    partyMode = !partyMode;
  }

  lastButton2 = current;
}

void loop() {

  handleButton1();
  handleButton2();

  int potValue = analogRead(potPin);
  int brightness = map(potValue, 0, 1023, 20, 255);

  }

  if (partyMode) {
    partyEffect();
    FastLED.setBrightness(brightness);
  }

  FastLED.show();

  delay(30);
}

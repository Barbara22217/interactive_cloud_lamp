#include <FastLED.h>

#define LED_PIN 3
#define NUM_LEDS 60

#define BUTTON_PIN 2
#define POT_PIN A0

#define TRIG_PIN 9
#define ECHO_PIN 10

CRGB leds[NUM_LEDS];

int mode = 0;
bool lastButtonState = HIGH;

long duration;
int distance;

void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
 

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {

  checkButton();

  if(mode == 0) manualMode();
  if(mode == 1) gestureMode();
  if(mode == 2) partyMode();

  FastLED.show();
}

void checkButton() {

  bool buttonState = digitalRead(BUTTON_PIN);

  if(buttonState == LOW && lastButtonState == HIGH) {

    mode++;

    if(mode > 3)
      mode = 0;

    delay(300);
  }

  lastButtonState = buttonState;
}

void manualMode() {

  int potValue = analogRead(POT_PIN);
  int brightness = map(potValue,0,1023,0,255);

  FastLED.setBrightness(brightness);

  for(int i=0;i<NUM_LEDS;i++)
    leds[i] = CRGB::White;
}

void gestureMode() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.034 / 2;

  int brightness = map(distance,5,40,255,30);
  brightness = constrain(brightness,30,255);

  FastLED.setBrightness(brightness);

  for(int i=0;i<NUM_LEDS;i++)
    leds[i] = CRGB::Blue;
}

void partyMode() {

  int potValue = analogRead(POT_PIN);
  int brightness = map(potValue,0,1023,80,255);

  FastLED.setBrightness(brightness);

  for(int i=0;i<NUM_LEDS;i++) {

    if(random(10) > 7)
      leds[i] = CHSV(random(255),255,255);
    else
      leds[i].fadeToBlackBy(40);

  }

  delay(40);
  }
}

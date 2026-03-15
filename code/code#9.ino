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
const int trigPin = 9;
const int echoPin = 10;
const int tiltPin = 7;

// Lamp states
bool lampOn = true;
bool partyMode = false;
bool breathingMode = false;
bool stormMode = false;

int colorIndex = 0;

// button variables
unsigned long pressStart = 0;
bool buttonActive = false;
bool longPressTriggered = false;

// button 2
bool lastButton2 = HIGH;

// breathing
int breathBrightness = 0;
int breathDirection = 2;

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
  pinMode(tiltPin, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  FastLED.clear();
  FastLED.show();
}

long getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  long distance = duration * 0.034 / 2;

  return distance;
}

void partyEffect() {

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(random8(), 255, 255);
  }
}

void breathingEffect(int baseBrightness) {

  breathBrightness += breathDirection;

  if (breathBrightness <= 10 || breathBrightness >= baseBrightness)
    breathDirection *= -1;

  fill_solid(leds, NUM_LEDS, colors[colorIndex]);
  FastLED.setBrightness(breathBrightness);
}

void normalLight(int brightness) {

  fill_solid(leds, NUM_LEDS, colors[colorIndex]);
  FastLED.setBrightness(brightness);
}

void stormEffect() {

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  int flashes = random(3,7);

  for(int i=0;i<flashes;i++){

    int pos = random(NUM_LEDS);
    int size = random(5,20);

    for(int j=0;j<size;j++){
      if(pos+j < NUM_LEDS)
        leds[pos+j] = CRGB::White;
    }

    FastLED.setBrightness(255);
    FastLED.show();

    delay(random(30,80));

    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();

    delay(random(80,200));
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

  // ultrasonic sensor
  long distance = getDistance();

  if (distance > 0 && distance < 20)
    breathingMode = true;
  else
    breathingMode = false;

  // tilt switch
  if (digitalRead(tiltPin) == HIGH)
    stormMode = true;

  if (!lampOn) {
    FastLED.clear();
    FastLED.show();
    delay(20);
    return;
  }

  if (stormMode) {
    stormEffect();
    stormMode = false;
    return;
  }

  if (partyMode) {
    partyEffect();
    FastLED.setBrightness(brightness);
  }
  else if (breathingMode) {
    breathingEffect(brightness);
  }
  else {
    normalLight(brightness);
  }

  FastLED.show();

  delay(30);
}

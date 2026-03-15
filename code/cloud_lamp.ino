#include <FastLED.h>

#define LED_PIN 3
#define NUM_LEDS 60
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

// pins
const int button1 = 6;
const int button2 = 2;
const int potPin = A0;
const int touchPin = 4;

// states
bool lampOn = true;
bool partyMode = false;
bool breathingMode = false;

int colorIndex = 0;

// button handling
unsigned long pressStart = 0;
bool buttonActive = false;
bool longPressTriggered = false;

bool lastButton2 = HIGH;
bool lastTouch = LOW;

// breathing
int breathBrightness = 0;
int breathDirection = 1;

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
  pinMode(touchPin, INPUT);

  FastLED.clear();
  FastLED.show();
}

void partyEffect() {

  for(int i=0;i<NUM_LEDS;i++){
    leds[i] = CHSV(random8(),255,255);
  }
}

void breathingEffect(int maxBrightness){

  static unsigned long lastUpdate = 0;
  static float phase = 0;

  int minBrightness = 80;   
  float speed = 0.05;      

  if(millis() - lastUpdate > 20){

    phase += speed;

    if(phase > TWO_PI)
      phase = 0;

    float wave = (sin(phase) + 1.0) / 2.0;   

    int brightness = minBrightness + wave * (maxBrightness - minBrightness);

    fill_solid(leds, NUM_LEDS, colors[colorIndex]);
    FastLED.setBrightness(brightness);

    lastUpdate = millis();
  }
}

void normalLight(int brightness){

  fill_solid(leds, NUM_LEDS, colors[colorIndex]);
  FastLED.setBrightness(brightness);
}

void handleButton1(){

  bool btn = digitalRead(button1);

  if(btn == LOW && !buttonActive){
    buttonActive = true;
    longPressTriggered = false;
    pressStart = millis();
  }

  if(btn == LOW && buttonActive && !longPressTriggered){

    if(millis() - pressStart > 700){

      colorIndex++;

      if(colorIndex > 2)
        colorIndex = 0;

      longPressTriggered = true;
    }
  }

  if(btn == HIGH && buttonActive){

    if(!longPressTriggered){
      lampOn = !lampOn;
    }

    buttonActive = false;
  }
}

void handleButton2(){

  bool current = digitalRead(button2);

  if(lastButton2 == HIGH && current == LOW){
    partyMode = !partyMode;
  }

  lastButton2 = current;
}

void handleTouch(){

  bool touchState = digitalRead(touchPin);

  if(lastTouch == LOW && touchState == HIGH){
    breathingMode = !breathingMode;
  }

  lastTouch = touchState;
}

void loop(){

  handleButton1();
  handleButton2();
  handleTouch();

  int potValue = analogRead(potPin);
  int brightness = map(potValue,0,1023,20,255);

  if(!lampOn){
    FastLED.clear();
    FastLED.show();
    delay(20);
    return;
  }

  if(partyMode){
    partyEffect();
    FastLED.setBrightness(brightness);
  }
  else if(breathingMode){
    breathingEffect(brightness);
  }
  else{
    normalLight(brightness);
  }

  FastLED.show();
  delay(30);
}

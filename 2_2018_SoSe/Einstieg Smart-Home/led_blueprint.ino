#define FASTLED_ALLOW_INTERRUPTS 0

#include "FastLED.h"

#define DATA_PIN    D4
#define NUM_LEDS    10

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000);
  FastLED.addLeds<WS2811,DATA_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,500);

  leds[0].red   = 255;
  leds[0].green = 0;
  leds[0].blue  = 0;

  leds[9][0] = 255;  // red
  leds[9][1] = 0; // green
  leds[9][2] = 0; // blue

  leds[1] = CRGB( 255, 0, 0);

  leds[2] = 0xFF0000;

  leds[3] = CRGB::Red;

  leds[4].setRGB( 255, 0, 0);

  leds[5] = leds[4];

  FastLED.show(); 
  delay(30); 
  
}

void loop() {
  
  

}

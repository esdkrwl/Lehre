#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include "FastLED.h"


#define DATA_PIN    D8
#define NUM_LEDS    3

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000);
  FastLED.addLeds<WS2811,DATA_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,500);

  leds[0].red   = 255;
  leds[0].green = 0;
  leds[0].blue  = 0;

  leds[1] = CRGB( 255, 0, 0);

  leds[2] = 0xFF0000;


  FastLED.show(); 
  delay(30); 
  
}

void loop() {
  
  

}

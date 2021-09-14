//Besonderheiten der FastLED Bibliothek im Zusammenspiel mit ESP8266
#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

//Bibliothek einbinden
//https://github.com/FastLED/FastLED/wiki/Pixel-reference
#include "FastLED.h"

//Pin, an welchem die LED angeschlossen ist, festlegen
#define DATA_PIN    D3
//Anzahl der angeschlossenen LEDs
#define NUM_LEDS    3
//LED Array mit NUM_LEDS Elementen
CRGB leds[NUM_LEDS];


// Setup Methode: dieser Code wird nur ein einziges mal inital beim Start ausgeführt
void setup() {
  //warte 3 Sekunden bevor es los geht
  delay(3000);
  //Init
  FastLED.addLeds<WS2811,DATA_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //Setze Helligkeit der LEDs auf 50 von max 255
  FastLED.setBrightness(50);
  //maximalen Strom auf 500 mA beschränken
  FastLED.setMaxPowerInVoltsAndMilliamps(5,500);
  // ???
  leds[0].red   = 255;
  leds[0].green = 0;
  leds[0].blue  = 0;
  // ???
  leds[1] = CRGB( 255, 0, 0);
  // ???
  leds[2] = 0xFF0000;
  // ???
  FastLED.show(); 
  delay(30); 
  
}

// Loop Methode: dieser Code wird in einer Endlosschleife ausgeführt, nachdem setup() ausgeführt wurde
void loop() {
  
}

/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

#define BLYNK_PRINT Serial

#include "FastLED.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define DATA_PIN    D3
#define NUM_LEDS    8
//LED Array mit NUM_LEDS Elementen
CRGB leds[NUM_LEDS];

//Var für aktuelle Animation
int animation = 0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "**********";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "**********";
char pass[] = "***********";

//Aufgabe 4.1
BLYNK_WRITE(V1) //Button Widget is writing to pin V1
{
  //für Aufgabe 4.4 zum Deaktivieren der Animation
  animation = 0;
  int pinData = param.asInt();
  Serial.println(pinData);
  if (pinData) {
    for (int i = 0; i <= 7; i++) {
      leds[i] = CRGB( 255, 0, 0);
    }
  } else {
    for (int i = 0; i <= 7; i++) {
      leds[i] = CRGB( 0, 0, 0);
    }
  }
  FastLED.show();
}

//Aufgabe 4.2
BLYNK_WRITE(V0) //Button Widget is writing to pin V1
{
  int pinData = param.asInt();
  FastLED.setBrightness(pinData);
  FastLED.show();
}

//Aufgabe 4.3
BLYNK_WRITE(V2) // zeRGBa assigned to V1
{
  //für Aufgabe 4.4 zum Deaktivieren der Animation
  animation = 0;
  // get a RED channel value
  int r = param[0].asInt();
  // get a GREEN channel value
  int g = param[1].asInt();
  // get a BLUE channel value
  int b = param[2].asInt();
  for (int i = 0; i <= 7; i++) {
    leds[i] = CRGB( r, g, b);
  }
  FastLED.show();
}

//Aufgabe 4.4
BLYNK_WRITE(V4)
{
  switch (param.asInt()) {
    case 1: {
        Serial.println("Animation 1");
        animation = 1;
        break;
      }
    case 2: {
        Serial.println("Animation 2");
        animation = 2;
        break;
      }
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "iot.informatik.uni-oldenburg.de", 8080);
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //?????
  FastLED.setBrightness(50);
  //?????
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);
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
  // ???
  delay(30);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  if (animation == 1) {
    leds[0].red   = 255;
    leds[0].green = 0;
    leds[0].blue  = 0;
    FastLED.show();
    delay(500);
    leds[0].red   = 0;
    leds[0].green = 255;
    leds[0].blue  = 0;
    FastLED.show();
    delay(500);
  }
  if (animation == 2) {
    leds[0].red   = 100;
    leds[0].green = 110;
    leds[0].blue  = 110;
    FastLED.show();
    delay(500);
    leds[0].red   = 0;
    leds[0].green = 0;
    leds[0].blue  = 0;
    FastLED.show();
    delay(500);
  }

}

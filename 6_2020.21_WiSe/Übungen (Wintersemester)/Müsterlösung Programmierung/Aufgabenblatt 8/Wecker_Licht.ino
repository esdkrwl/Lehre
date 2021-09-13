#define FASTLED_INTERNAL
#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "FastLED.h"


#define BUTTON   D6
#define DATA_PIN D2
#define NUM_LEDS  8

// LED array 
CRGB leds[NUM_LEDS];

// WiFi credentials.
const char ssid[] = "";
const char pass[] = "";

// Blynk server endpoint config
const char server[] = "iot.informatik.uni-oldenburg.de";
const int port = 8080;

// Blynk auth token.
const char auth[] = "";

// NTP time offset, because GMT+1
const long utcOffsetInSeconds = 3600;

// NTP UDP connection object
WiFiUDP ntpUDP;

// NTP client object which uses the UDP as the transport protocoll
NTPClient timeclient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

// Global time as a sting hh:mm:ss
String gTime = "";

// 1800 Secounds = 30 Minutes
int gTimeCountDown = 1800;

// Seconds left to the "alarm"
long gWakeUpCountdown = -1;

// Current time in seconds
long gTimeInSeconds = 0;

// Current time sperate in hour, minute and second
int gHour = 0;
int gMinute = 0;
int gSecond = 0;

// Brightness level for the LED strip
int gBrightness = 0;

/*
 * Blynk timer wiget
 * Takes the parameter and creates a global wakeup timer
 * 
 */
BLYNK_WRITE(V1) {
  long wakeTimeInSeconds = param[0].asLong();
  gWakeUpCountdown = wakeTimeInSeconds;
  Serial.println(gWakeUpCountdown);
}

/*
 * Blynk button 
 * Swichtes the brightness to 0
 * 
 */
BLYNK_WRITE(V2) {
  int off = param.asInt();
  if(off){
    Serial.println("Shutdown the brightness");
    gBrightness = 0;
  }
}

/*
 * Checks if the time difference is between the global wakeup-coundown 
 * and the global time in seconds.
 * 
 */

void checkTime(){
  if(gWakeUpCountdown < 0){
    return;
  }

  int difference = gWakeUpCountdown - gTimeInSeconds;
  if(difference <= gTimeCountDown){
    if(difference > 1500){
      gBrightness = 10;
    }
    if(difference < 1500 && difference > 1200){
      gBrightness = 20;
    }
    if(difference < 1500 && difference > 1200){
      gBrightness = 30;
    }
    if(difference < 1200 && difference > 900){
      gBrightness = 40;
    }
    if(difference < 900 && difference > 600){
      gBrightness = 50;
    }
    if(difference < 600 && difference > 300){
      gBrightness = 60;
    }
    if(difference < 300 && difference > 150){
      gBrightness = 70;
    }
    if(difference < 150 && difference > 120){
      gBrightness = 80;
    }
    if(difference < 120 && difference > 60){
      gBrightness = 90;
    }
    if(difference < 60 && difference >= 0){
      gBrightness = 100;
    }
    if(difference < 0){
      Serial.println("Resetting the countdown.");
      gWakeUpCountdown = -1;
      return;
    }

    FastLED.setBrightness(gBrightness);
    FastLED.show();
    Serial.print(difference);
    Serial.println(" Seconds left");
  }
}

/*
 * Read the button on the breadboard
 * If 1 switches the brightness to 0
 * 
 */
void readBrightnessButton(){
  int off = digitalRead(BUTTON);
  if(off){
    gBrightness = 0;
    FastLED.setBrightness(gBrightness);
    FastLED.show();
    Serial.println("Pushed");
  }
}

void setup(){
  // Wait for the capacitor to be fully charged
  delay(3000);
  // Add the leds to a global object
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(gBrightness);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);
  
  for(int i = 0; i < 8; i++){
    leds[i] = CRGB( 255, 147, 51);  
  }
  
  FastLED.show();
  delay(30);
  
  // Setup the serial connection for logging
  Serial.begin(115200);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(BUTTON, INPUT);
  
  // Begin the WiFi connection with the provided credentials
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting ...");
    delay(200);
  }
  
  timeclient.begin();
  Blynk.config(auth, server, port);
  Blynk.connect();
}

void loop()
{
  timeclient.update();
  Blynk.run();

  gTime = timeclient.getFormattedTime();
  
  Serial.print("Current time: ");
  Serial.println(gTime);

  gHour = timeclient.getHours();
  gMinute = timeclient.getMinutes();
  gSecond = timeclient.getSeconds();

  gTimeInSeconds = (gHour * 60 * 60) + (gMinute * 60) + gSecond;

  checkTime();
  readBrightnessButton();
  delay(1000);
}

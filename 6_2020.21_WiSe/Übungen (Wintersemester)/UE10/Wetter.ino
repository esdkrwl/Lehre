#include <FastLED.h>
#include <ArduinoJson.h>                  
#include <math.h>                         
#include <WiFiManager.h>  
                
#define BRIGHTNESS 64
#define DATA_PIN D3 
#define NUM_LEDS 8   

CRGB leds[NUM_LEDS];

WiFiManager wifiManager;
WiFiClient client;

// ========================  hier deinen API-Key eintragen!!!  ============================================================================================================
const String city = "Oldenburg";
const String api_key = "xxx";    // dein Open-Weather-Map-API-Schluessel, kostenlos beziehbar ueber https://openweathermap.org/
// ========================================================================================================================================================================

int weatherID = 0;
int weatherID_shortened = 0;
String weatherforecast_shortened = " ";
int temperature_Celsius_Int = 0;
unsigned long lastcheck = 0;                      

void setup() {
  Serial.begin(115200);    
 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);
  FastLED.clear();
  FastLED.show();
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB( 253, 184, 19);
  }
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
  
  wifiManager.autoConnect("deineWetterLampe");
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB( 0, 0, 0);
  }
  FastLED.show();
  delay(2000);
  getCurrentWeatherConditions();
}

void loop() {
  
  if (millis() - lastcheck >= 1800000) {         
    getCurrentWeatherConditions();
    lastcheck = millis();                         
  }
  
  if (weatherID == 800){
    LED_effect_clearSky();
  }
  else {
    switch (weatherID_shortened) {
      case 8: LED_effect_cloudy(); break;
    }
  }

}

void getCurrentWeatherConditions() {
  int WeatherData;
  Serial.print("connecting to "); Serial.println("api.openweathermap.org");
  if (client.connect("api.openweathermap.org", 80)) {
    client.println("GET /data/2.5/weather?q=" + city + ",DE&units=metric&lang=de&APPID=" + api_key);
    client.println("Host: api.openweathermap.org");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("connection failed");
  }
  const size_t capacity = JSON_ARRAY_SIZE(2) + 2 * JSON_OBJECT_SIZE(1) + 2 * JSON_OBJECT_SIZE(2) + 2 * JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(14) + 360;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, client);
  client.stop();

  weatherID = doc["weather"][0]["id"];
  int temperature_Celsius = doc["main"]["temp"];
  temperature_Celsius_Int = (int)temperature_Celsius;
  weatherID_shortened = weatherID / 100;
  switch (weatherID_shortened) {                                    
    //...
    case 8: weatherforecast_shortened = "Wolken"; break;
    default: weatherforecast_shortened = ""; break;
  } if (weatherID == 800) weatherforecast_shortened = "klar";            
}

void fade(int led_position, uint16_t duration, uint16_t delay_val, uint16_t startR, uint16_t startG, uint16_t startB, uint16_t endR, uint16_t endG, uint16_t endB) {
  int16_t redDiff = endR - startR;
  int16_t greenDiff = endG - startG;
  int16_t blueDiff = endB - startB;
  int16_t steps = duration * 1000 / delay_val;
  int16_t redValue, greenValue, blueValue;
  for (int16_t i = 0 ; i < steps - 1 ; ++i) {
    redValue = (int16_t)startR + (redDiff * i / steps);
    greenValue = (int16_t)startG + (greenDiff * i / steps);
    blueValue = (int16_t)startB + (blueDiff * i / steps);
    leds[0] = CRGB(redValue, greenValue, blueValue);
    FastLED.show();
    delay(delay_val);
  }
  leds[led_position] = CRGB(endR, endG, endB);
}

void LED_effect_clearSky() { // Effekt, der angezeigt wird, wenn der Himmel klar ist
  FastLED.setBrightness(255);
  leds[0] = CRGB::Yellow;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
}

void LED_effect_cloudy() {
}

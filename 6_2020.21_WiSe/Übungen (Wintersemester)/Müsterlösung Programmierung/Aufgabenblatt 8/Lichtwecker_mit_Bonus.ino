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
#include <TimeLib.h>
#include <WidgetRTC.h>

#define DATA_PIN    D3
#define BUTTON_PIN  D5
//???
#define NUM_LEDS    8
//LED Array mit NUM_LEDS Elementen
CRGB leds[NUM_LEDS];

BlynkTimer timer;

WidgetRTC rtc;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xxx";
char pass[] = "xxx";

//Es müssen 8 Einträge reserviert werden, damit wochentage kompatibel zu t.isWeekdaySelected(i) ist. Dort beginnt i nämlich ab 1.
//wochentage[0] wird nur angelegt, aber nicht benutzt. Der Rest liest sich: wochentage[1] entspricht Montag. Wenn wochentage[1] = 0, dann ist kein Wecktag. Wenn Wenn wochentage[1] = 1, dann ist Wecktag.
int wochentage[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int weckstunde = 0;
int weckminute = 0;

bool wecktag_erreicht = false;
bool weckzeit_erreicht = false;

// Mit dieser Variable kann der Wecker entweder per App oder per Taster ausgeschaltet werden
bool alarm_enabled = false;

//maximale Helligkeit bei 255 erreicht, alle 10s wird Lichtwecker aufgerufen und nach 30min miximale Helligkeit erreichen
//D.h. es müssen 255 diskrete Werte auf 1800s (=30min) in 10s Schritten verteilt werden. 255 / (1800/10) = 1.42. Da setBrightness, aber einen Integer erwartet, erhöhen wir die Helligkeit alle 10s um 1 und starten dafür nicht bei 0, sondern bei 255 - 180 = 75
int brightness = 75;


//Tagesumrechnung, da die Kodierung der Tage in Blynk und der Zeit Lib nicht konsistent sind. Sonntag ist in der Time Lib Tag 1 und in der Blynk App Tag 7
int today () {
  int dayadjustment = -1;
  if (weekday() == 1) {
    dayadjustment = 6;
  }
  return weekday() + dayadjustment;
}


void check_wecktag() {
  //prüfe, ob heute Wecktag ist..
  if (wochentage[today()]) {
    //aktiviere den Wecker!
    alarm_enabled = true;
    //Blynk App zurückmelden, dass Alarm jetzt an ist.
    Blynk.virtualWrite(V1, 1);

    Serial.println("Heute ist Wecktag!");
    wecktag_erreicht = true;
    //Weckzeit berechnen: Der Wecker muss ja 30min vorher anfangen uns mit Licht zu wecken. Daher müssen wir die tatsächliche Weckzeit 30min zurück setzen
    //falls die Minuten minus 30 größer als 0 sind (z.B. Wecker um 09:40 -> Weckzeit 09:10), dann..
    if (weckminute - 30 >= 0) {
      //.. bleiben die Stunden, wie sie sind
      //.. und von den Minuten ziehen wir 30 ab
      weckminute = weckminute - 30;
      //falls nicht (z.B. 09:25 -> 08:55)
    } else {
      weckminute = 60 - (60 - weckminute - 30);
      weckstunde =  weckstunde - 1;
      if (weckstunde < 0) {
        weckstunde = 23;
      }
      Serial.println("Berechnete Weckzeit: " + String(weckstunde) + ":" + String(weckminute));
    }
  } else {
    Serial.println("Heute kein Wecktag!");
    wecktag_erreicht = false;
  }

}

//Methode zum Prüfen der aktuellen Uhrzeit. Wird zudem genutzt, um festzustellen, ab wann die LED angeschaltet wird
void clockDisplay()
{
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();

  //falls Alarm aktiviert ist...
  if (alarm_enabled) {
    Serial.println("Alarm");
    // und wir zusätzlich einen Wecktag haben ...
    if (wecktag_erreicht) {
      Serial.println("Wecktag");
      // und wir zusätzlich die berechnete Weckzeit erreicht haben
      if (weckstunde == hour() && weckminute == minute()) {
        weckzeit_erreicht = true;
        Serial.println("Weckzeit");
      }
      // dann wird alle 10s der Helligkeitswert um 1 erhöht bis maximal 255.
      if (weckzeit_erreicht) {
        FastLED.setBrightness(brightness);
        brightness++;
        //sicherstellen, dass set.setBrightness niemals einen Wert über 255 bekommen kann (falls ich mich verrechnet haben sollte..)
        brightness = min(brightness++, 255);
        Serial.println(brightness);
        FastLED.show();
      }
    }
  }

  //Um Mitternacht prüfen, ob heute Wecktag ist.
  if (hour() == 0 and minute() == 0) {
    check_wecktag();
  }
}

BLYNK_WRITE(V0)
{
  TimeInputParam t(param);

  if (t.hasStartTime())
  {
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute() + ":" +
                   t.getStartSecond());
  }


  //gehe alle Tage der Woche durch
  for (int i = 1; i <= 7; i++) {
    //und übertrage diese ins Array wochentage, aber täglich um Mitternacht in check_wecktag festgestellt werden kann, ob heute Wecktag ist.
    wochentage[i] = t.isWeekdaySelected(i);
    if (t.isWeekdaySelected(i)) {
      Serial.println(String("Day ") + i + " is selected");
    }
  }
  //Das ist zunächst die Weckzeit, die in der App eingestellt wurde.
  weckstunde = t.getStartHour();
  weckminute = t.getStartMinute();
  Serial.println("Eingetragene Weckzeit: " + String(weckstunde) + ":" + String(weckminute));
  //Prüfe, ob heute Wecktag ist..
  check_wecktag();
}

//App Schalter, um den Alarm zu aktivieren/deaktivieren. Zusätzlich kann beim deaktivieren die LED ausgeschaltet werden.
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();

  if (pinValue) {
    alarm_enabled = true;
  } else {
    alarm_enabled = false;
    // alle LEDs aus
    FastLED.setBrightness(0);
    FastLED.show();
    //Helligkeitswert auf 75 zurück setzen für den nächsten Alarm
    brightness = 75;
  }
}


BLYNK_CONNECTED() {
  // Synchronize time on connection
  rtc.begin();
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "iot.informatik.uni-oldenburg.de", 8080);
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);

  for (int i = 0; i < NUM_LEDS; i++) {
    // https://www.colorcombos.com/colors/FDB813
    leds[i] = CRGB( 253, 184, 19);
  }
  FastLED.setBrightness(0);
  FastLED.show();

  setSyncInterval(10 * 60); // Sync interval in seconds (10 minutes)
  // Alle 10s die Systemzeit prüfen
  timer.setInterval(10000L, clockDisplay);

}

void loop()
{
  Blynk.run();
  timer.run();
  //Falls der physische Taster gedrückt wird
  if (digitalRead(BUTTON_PIN)) {
    //.. wird der Alarm deaktiviert
    alarm_enabled = false;
    //.. und alle LEDs ausgeschaltet
    FastLED.setBrightness(0);
    FastLED.show();
    //Helligkeitswert auf 75 zurück setzen für den nächsten Alarm
    brightness = 75;
    //Blynk App sagen, dass Wecker aus ist.
    Blynk.virtualWrite(V1, 0);
  }
}

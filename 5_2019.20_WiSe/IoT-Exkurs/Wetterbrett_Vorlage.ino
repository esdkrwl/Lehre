/*
 * Einstiegsbeispiel für das Wetterbrett-Projekt
 */
//Besonderheiten der FastLED Bibliothek im Zusammenspiel mit ESP8266
#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

//Bibliothek einbinden
#include "FastLED.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//Pin, an welchem die LED angeschlossen ist, festlegen
#define DATA_PIN    D3
//Anzahl der angeschlossenen LEDs
#define NUM_LEDS    3
//LED Array mit NUM_LEDS Elementen
CRGB leds[NUM_LEDS];

// Für das eigene Netzwerk anpassen
const char* ssid = "Lernlabor-Gast";
const char* password = "Prometheus@DDI";

//MQTT Broker und Topic festlegen. Weitere Infos zu MQTT hier: https://www.hivemq.com/mqtt-essentials/
const char* mqtt_server = "mqtt.iot.informatik.uni-oldenburg.de";
const char* mqtt_topic = "wetterID/Oldenburg/morgen";

WiFiClient espClient;
PubSubClient client(espClient);

//Methode, damit sich der Mikrocontroller mit dem WiFi Netzwerk verbindet
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//Callback aufgerufen, sobald es neue Daten vom MQTT Broker gibt
void callback(char* topic, byte* payload, unsigned int length) {
  char receivedPayload[length];
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    receivedPayload[i] = (char) payload[i];
  }
  Serial.println();

  //Ziffern aus dem Array zu einer Zahl umwandeln
  int wetterID = atoi(receivedPayload);
  //Mögliche Antworten vom Server für das Wetter morgen: https://openweathermap.org/weather-conditions
  if(wetterID == 500){
    Serial.println("Sieht nach Regen aus..");
    leds[0] = CRGB( 0, 0, 255);
    FastLED.show();
  }


}

// Methode, um sich mit dem MQTT Broker erneut verbinden zu können..
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  delay(3000);
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  //Init LED Strip
  FastLED.addLeds<WS2811,DATA_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //Setze Helligkeit der LEDs auf 50 von max 255
  FastLED.setBrightness(50);
  //maximalen Strom auf 500 mA beschränken
  FastLED.setMaxPowerInVoltsAndMilliamps(5,500);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

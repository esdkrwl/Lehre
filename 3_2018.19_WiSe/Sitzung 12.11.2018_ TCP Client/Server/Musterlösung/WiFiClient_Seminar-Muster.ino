#include <ESP8266WiFi.h>
#define BUTTON D0

const char* ssid     = "ESP8266";
const char* password = "FFEEDDCCBB";

const char* host = "192.168.178.36";
const int httpPort = 80;

byte state = LOW;

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  pinMode(BUTTON, INPUT);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  //falls Button gedrückt wird
  if(digitalRead(BUTTON)){
    //verbinde dich mit dem Server
      Serial.print("connecting to ");
      Serial.println(host);
    
      // Use WiFiClient class to create TCP connections
      WiFiClient client;
    
      if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
      }  
    //prüfe ob zuvor eine LOW oder HIGH versendet wurde
    if(state){
      Serial.println("on");
      client.print("on#");  
    } else {
      Serial.println("off");
      client.print("off#");
    }
    //toggle den Zustand
    state = !state;
    
    //baue kurzes delay um Prellen des Tasters zu verbindern.
    delay(250);
   }
}


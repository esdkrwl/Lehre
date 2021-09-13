#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "ESP8266";
const char* password = "FFEEDDCCBB";
const char* mqtt_server = "3L15t4.xyz";
const char* mqtt_topic_publish = "irgendwas/irgendwas/1";
const char* mqtt_topic_subscribe = "irgendwas/irgendwas/2";


WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
int val = 0;

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

void callback(char* topic, byte* payload, unsigned int length) {
  char receivedPayload[length];
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    receivedPayload[i] = (char) payload[i];
  }

}

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
      client.subscribe(mqtt_topic_subscribe);
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
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (millis() - lastMsg > 5000) {
  lastMsg = millis();

  // Publish Char Array (einfachste Methode)
  client.publish(mqtt_topic_publish, "Hallo Welt");

  // Publish String (String muss in ein Char-Array umgewandelt werden)
  String payload = "Hallo Welt";
  //Erzeuge Char Array der Länge der Strings + 1 für den Nullterminator am Ende
  char payload_buff[payload.length()+1];
  // Wandelt String mit dem Befehl toCharArray(buf, len) in Array um
  payload.toCharArray(payload_buff, payload.length()+1);
  //uund abschicken
  client.publish(mqtt_topic_publish, payload_buff);

  // Publish JSON (JSON String muss ebenfalls in Char Array umgewandelt werden. Verfahren ist vollkommen analog zu oben)
  ++val;
  String json_payload = "{\"message\":\"Hallo Welt\",\"number\":" + String(val) + "}";
  char json_payload_buff[json_payload.length()+1];
  json_payload.toCharArray(json_payload_buff, json_payload.length()+1);
  client.publish(mqtt_topic_publish, json_payload_buff);

  // Publish int (auch hier muss die Zahl erst in einen String umgewandelt werden, damit wir daraus ein Array machen können)
  String val_str = String(val);
  char val_buff[val_str.length()+1];
  val_str.toCharArray(val_buff, val_str.length()+1);
  client.publish(mqtt_topic_publish, val_buff);

  // Publish float (auch hier wieder char array)
  float pi = 3.14;
  String pi_str = String(pi);
  char pi_buff[pi_str.length()+1];
  pi_str.toCharArray(pi_buff, pi_str.length()+1);
  client.publish(mqtt_topic_publish, pi_buff);


  }
}
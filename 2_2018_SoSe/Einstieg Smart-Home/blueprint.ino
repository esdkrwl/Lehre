#include <ESP8266WiFi.h>
#include <PubSubClient.h>
//HIER KÖNNTE IHRE LED LIBRARY EINGEBUNDEN WERDEN

//Credentials des Netzwerks
const char* ssid = "ESP8266";
const char* password = "FFEEDDCCBB";
//MQTT Daten
const char* mqtt_server = "iot.eclipse.org";
//Beispieltopics
const char* dein_topic_1 = "hallo/welt";
const char* dein_topic_2 = "hello/welt/3";

/*
 * Platzhalter LED-Streifen
 * HIER KÖNNTE IHRE LED FESTGELEGT WERDEN
 */

WiFiClient esp_wifi_client;
PubSubClient mqtt_client(esp_wifi_client);

/*
 * Methode zum Verbinden mit dem Netzwerk
 */
void setup_wifi() {

  delay(10);
  
  Serial.println();
  Serial.print("Baue Verbindung auf zum Netzwerk ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  // Warte bis Verbindung zum Netzwerk aufgebaut wurde
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Paar nützliche Netzwerkdaten
  Serial.println("");
  Serial.println("Verbindung aufgebaut. Yeah!");
  
  Serial.println("IP Adresse: ");
  Serial.println(WiFi.localIP());
  
  Serial.println("Mac Adresse: ");
  Serial.println(WiFi.macAddress());
  
  Serial.println("Signalstärke: ");
  Serial.println(WiFi.RSSI());
}


/*
 * MQTT-Callback Methode.
 * Diese Methode wird jedes Mal aufgerufen, wenn unter
 * den abonnierten Topics neue Daten zu Verfügung stellen.
 * Als Parameter wird das char-Array topic, welches das Topic
 * der empfangenden Nachricht enthält, das byte-Array payload,
 * welches die Daten enthält und die Länge der Nachricht.
 */
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Neue Nachricht empfangen [");
  Serial.print(topic);
  Serial.print("]: ");
  //Speicher im Buffer den Payload als String zwischen
  char payload_buffer[length];
  /*
   * Gehe das Byte-Array für jedes Element durch,
   * führe typecasting von byte auf char durch und gebe
   * char in der Konsole aus
   */
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    payload_buffer[i] = (char)payload[i];
  }
  payload_buffer[length] = '\0';
  Serial.println();

  /*
   * Falls ihr die Topics auswerten möchtet, könnt ihr
   * die C-Funktion strcmp, um char Arrays mit einander
   * vergleichen zu können.
   * strcmp gibt eine 0 zurück, falls genau 0 Stellen der
   * beiden Arrays unterschiedlich sind -> beide char Arrays
   * sind identisch
   */
  if(strcmp(topic, dein_topic_1) == 0){
    /*
     * Analog dazu kann man den Payload auswerten
     */
     if(strcmp(payload_buffer, "led_an") == 0){
  
     }
  }
}

/*
 * Methode um einen erneuten Verbindungsversuch 
 * zum MQTT-Broker vorzunehmen
 */
void reconnect(){
  /*
   * Solange der Client nicht mit dem MQTT-Server 
   * nicht verbunden ist, bleibt die Firmware
   * in dieser while-Schleife gefangen
   */
  while (!mqtt_client.connected()){
    
    Serial.println("Baue Verbindung zum Broker auf...");

    /*
     * Verbinde mit Broker
     * Als Client ID wird einfach die Mac-Adresse verwendet,
     * um zu verhindern, dass sich mehrere Clients mit der
     * gleichen ID beim Broker anmelden möchten.
     * 
     * Da WiFi.macAddress() einen String zurück gibt,
     * mqtt_client.connect() jedoch ein char Array als Parameter
     * übergeben bekommen muss, wandeln wir den String in ein Array um
     */
    char* mac = "xx:xx:xx:xx:xx:xx";
    WiFi.macAddress().toCharArray(mac, WiFi.macAddress().length());
    if (mqtt_client.connect(mac)){
      /*
       * Wenn erfolgreich eine Verbindung aufebaut werden konnte,
       * gebe eine entsprechende Meldung in der Konsole aus.
       * Abonniere im Anschluss die oben definieren Topics
       */
      Serial.println("Yuhu. Verbindung aufgebaut");
      mqtt_client.subscribe(dein_topic_1);
      mqtt_client.subscribe(dein_topic_2);
      //HIER KÖNNTE DEIN TOPIC STEHEN
    } else {
      /*
       * Falls der Versuch fehlgeschlagen ist, versuchen wir
       * es in 5 Sekunden nochmal
       */
      Serial.println("Fehlgeschlagen... Reconnect in 5 Sekunden");
      delay(5000);
    }
  }
}

/*
 * Initialisiere Firmware
 *  - setze OnBoard LED auf Output
 *  - initialisiere serielle Verbindung zwischen PC und µC
 *  - baue Verbindung zum WiFi auf
 *  - hinterlege MQTT-Daten und setze Callback-Methode
 */
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  mqtt_client.setServer(mqtt_server, 1883);
  mqtt_client.setCallback(callback);
  // HIER KÖNNTE IHR LED-STREIFEN INITIALISIERT WERDEN
}

void loop() {
  /*
   * Prüfe regelmäßig, ob die Verbindung zum MQTT-Broker besteht.
   * Falls die Verbindung verloren geht, wird die
   * Methode reconnect aufgerufen, um die Verbindung
   * erneut aufzubauen.
   * 
   * Da im aller ersten Durchlauf das Gerät nicht mit dem
   * Broker verbunden sein kann, wird sofort reconnect()
   * aufgerufen.
   */
  if (!mqtt_client.connected()) {
    reconnect();
  }
  /*
   * Hier passiert MQTT Magic. Ihr müsst euch um nichts
   * kümmern.
   * Sobald neue Daten unter den abonierten Topics da sind,
   * wird unmittelbar die Callback-Methode aufgerufen
   */
  mqtt_client.loop();
}

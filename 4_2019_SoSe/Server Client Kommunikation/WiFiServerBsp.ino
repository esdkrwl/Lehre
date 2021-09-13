#include <Arduino.h>

#include <WiFi.h>

const char* ssid     = "ESP8266";
const char* password = "FFEEDDCCBB";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // set the LED pin mode

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();

}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {
        String req = client.readStringUntil('\r');
        Serial.println(req);
        String response = "";
        if(req.equals("Hallo Server")){
          // Prepare the response
          Serial.println("Hallo empfangen");
          response = "Hallo Client\r";
        } else {
          Serial.println("Irgendwas anderes empfangen");
          response = "Was?!\r";
        }
        client.flush();
        // Send the response to the client
        client.print(response);
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

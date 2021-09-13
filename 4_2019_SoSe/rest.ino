#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>

void getRequest(String resource, String item){
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");

    http.begin("http://3l15t4.xyz:8080/api/"+ resource + "/" + item); //HTTP

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if(httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            /*if(payload == "Beep Boop"){
                Serial.println("yes");
            }*/
            Serial.println(payload);
        }
    } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
}

void postRequest(String resource, String item, String payload){
    HTTPClient http;

    http.begin("http://3l15t4.xyz:8080/api/"+ resource + "/" + item);  //Specify destination for HTTP request
    http.addHeader("Content-Type", "text/plain");             //Specify content-type header

    int httpResponseCode = http.POST(payload);   //Send the actual POST request

    if(httpResponseCode > 0){

    String response = http.getString();                       //Get the response to the request

    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer

    }else{

        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);

      }

      http.end();  //Free resources

}

void putRequest(String resource, String item, String payload){
    HTTPClient http;

    http.begin("http://3l15t4.xyz:8080/api/"+ resource + "/" + item);  //Specify destination for HTTP request
    http.addHeader("Content-Type", "text/plain");             //Specify content-type header

    int httpResponseCode = http.PUT(payload);   //Send the actual PUT request

    if(httpResponseCode > 0){

    String response = http.getString();                       //Get the response to the request

    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer

    }else{

        Serial.print("Error on sending PUT: ");
        Serial.println(httpResponseCode);

      }

      http.end();  //Free resources

}

void setup() {
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println("ESP8266");

    WiFi.begin("ESP8266", "FFEEDDCCBB");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    if(WiFi.status()== WL_CONNECTED){
        //Frage auf der Ressource Tolij nach dem Inhalt des Items test
        getRequest("Ivan", "test");
        delay(5000);
        //Schreibe auf die Ressource Tolij "Hello World" in das Item test
        //Put verhält sich analog dazu
        postRequest("Ivan", "test", "Hello World");
        delay(500);
        //Frage auf der Ressource Tolij nach dem Inhalt des Items test. Hier müsste nun Hello World stehen
        getRequest("Ivan", "test");
        delay(5000);
        postRequest("Ivan", "test", "Beep Boop");
        delay(500);

    } else {
        Serial.println("Error in WiFi connection");
    }
    delay(5000);
}

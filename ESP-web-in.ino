/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Replace with your network credentials
const char* ssid = "Ilgner";
const char* password = "0123456789";

String ledState ;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "OUT1"){

int valor = 10;

ledState = valor;
   
    return ledState;
  }
    if(var == "OUT2"){

int valor = 25;

ledState = valor;
   
    return ledState;
  }

  
  return String();
}
 
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);


  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/estilo.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/estilo.css", "text/css");
  });



  // Start server
  server.begin();
}
 
void loop(){
  
}

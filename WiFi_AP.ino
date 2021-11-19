#include <ESP8266WiFi.h>              //Biblioteca Wifi para ESP8266
#include <WiFiClient.h>               //Biblioteca para Cliente Wifi do ESP8266
#include <ESP8266WebServer.h>

#define APSSID "JEAN_REDE"
static const char* ssid = APSSID;

/* Servidor */
ESP8266WebServer server(80);

/* Servidor */
void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected Jean </h1>");
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");

  Serial.println(myIP);

  /* Servidor */
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  
 /* Servidor */
 server.handleClient();
}

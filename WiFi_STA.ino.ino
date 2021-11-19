#include <ESP8266WiFi.h>              //Biblioteca Wifi para ESP8266
#include <WiFiClient.h>               //Biblioteca para Cliente Wifi do ESP8266
#include <ESP8266WebServer.h>

#define STASSID "IE 2.4G"
#define STAPSK  "IE24G12345"
#define HOST    "JEAN_STA"

/* Servidor */
ESP8266WebServer server(80);

/* Servidor */
void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected Jean </h1>");
}

const char* ssid     = STASSID;
const char* password = STAPSK;
const char* host     = HOST;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(host);
  // IP Fixo
  //WiFi.config(IP_statico, Mascara de Subrede, Gateway)
  WiFi.config(IPAddress(192,168,0,203),IPAddress(192,168,0,1), IPAddress(255,255,255,0), IPAddress(192,168,0,1));
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print("#");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  /* Servidor */
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  /* Servidor */
  server.handleClient();
}

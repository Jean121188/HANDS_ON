#include <ESP8266WiFi.h>              //Biblioteca Wifi para ESP8266
#include <WiFiClient.h>               //Biblioteca para Cliente Wifi do ESP8266
//#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>        //Para requisicoes HTTP

// defines
#define STASSID "IE 2.4G"
#define STAPSK  "IE24G12345"
#define HOST    "JEAN_STA"

// variaveis
const char* ssid     = STASSID;
const char* password = STAPSK;
const char* host     = HOST;

int count = 0;
String link = "";

unsigned long previousMillis = 0;

// funcoes
void SendDataGET(int count);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(host);
  // IP Fixo
  //WiFi.config(IP_statico, Mascara de Subrede, Gateway)
  //WiFi.config(IPAddress(192,168,0,203),IPAddress(192,168,0,1), IPAddress(255,255,255,0), IPAddress(192,168,0,1));
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print("#");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  unsigned long currentMillis = millis();  // incrementa 1 a cada 1ms      4000               
  
  if ((unsigned long)(currentMillis - previousMillis) >= 2000) // 2 segundos
  {
    count++;
    SendDataGET(count);
    previousMillis = currentMillis; // previousMillis = 4000
  }
}

void SendDataGET(int count)
{
  if(WiFi.status() == WL_CONNECTED)
  {
    WiFiClient client;
    HTTPClient http;
    
    link = "http://192.168.0.120:1880/api-node?id=1&count=" + String(count);
    Serial.println(link);
    
    http.begin(client, link);
    // Receita de BOLO para o Node-Red:
    // 192.168.0.120 -> é o IP pra onde queremos enviar
    // :1880 -> é a porta ao qual os dados "entrarão"
    // /api-node -> caminho ou URL no Node-Red
    // id=1&count= -> Variaveis que irao ser recebidas
    http.GET();
    Serial.println("Enviei...");
//    Serial.print("httpCode: ");Serial.println(httpCode);
    http.end();
  }
  else
  {
    Serial.print("Nao foi possivel enviar os dados: ");
  }
}

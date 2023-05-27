#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

const char* ssid = "<WIFI SSID>";
const char* pass = "<WIFI PASSWORD>";

const char* TOKEN = "<TOKEN BOT>";
const int CHAT_ID = <TELEGRAM CHAT ID>;

WiFiClient client;
HTTPClient httpClient;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,pass);
  
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  } 
  
  Serial.println("");
  Serial.println("Conectado al WIFI!");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());

  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure();

  String url = "https://api.telegram.org/bot" + String(TOKEN) + "/sendMessage";

  http.begin(client,url);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<200> jsonDoc;
  jsonDoc["chat_id"] = CHAT_ID;
  jsonDoc["text"] = "Hola desde ESP8266!";
  String jsonStr;
  serializeJson(jsonDoc,jsonStr);

  int httpResponseCode = http.POST(jsonStr);

  if (httpResponseCode > 0){
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  }

  else{
    Serial.println(httpResponseCode);
  }
  
  http.end();
}

void loop(){

}

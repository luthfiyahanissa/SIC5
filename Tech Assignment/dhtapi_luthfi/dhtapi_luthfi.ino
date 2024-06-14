#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "WiFi.h"
#include "DHT.h"

const int DHT_PIN = 15;
#define WIFI_SSID "SSID" 
#define WIFI_PASSWORD "pw" 
#define SERVER_ADDRESS "http://192.168.1.6:5000" 
#define SERVER_PORT 80 


DHT dht(DHT_PIN, DHT22);
void setup() {
  Serial.begin(115200);    
  dht.begin();
  connectToWiFi();
}

void loop() {
  
  HTTPClient http;
  String endpoint = String(SERVER_ADDRESS) + "/data";
  JsonDocument jsonDoc; 

  float  temp = dht.readTemperature();
  float hum = dht.readHumidity();
  Serial.println("Temp: " + String(temp, 2) + "°C");
  Serial.println("Humidity: " + String(hum, 1) + "%");

  jsonDoc["temp"] = temp;
  jsonDoc["hum"] = hum;

  String postData;
  serializeJson(jsonDoc, postData);
  http.begin(endpoint); 
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.print("HTTP Error code: ");
    Serial.println(httpResponseCode);
  }Serial.println("-----------------------");

  http.end();
  delay(10000); 
}

void connectToWiFi() {
 Serial.println("Connecting to WiFi");
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

 while (WiFi.status() != WL_CONNECTED) {
   delay(1000);
   Serial.println("Connecting...");
 }
 
 Serial.println("Connected to WiFi");
}

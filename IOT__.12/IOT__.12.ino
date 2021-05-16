#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#ifndef STASSID
#define STASSID "UPC94A438A"
#define STAPSK  "bj8x3kdrcsvY"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
//IPAddress dns(192, 168, 0, 1);  //Google dns

HTTPClient http;

void setup() {
  Serial.begin(9600);
  //WiFi.config()
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    
    delay(500);
    Serial.print(".");
  }
  //WiFi.setDNS(dns);
  Serial.print("Dns configured.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int randomVal = random(-50, 100);
    http.begin("http://192.168.0.101:1880/temperature?value="+String(randomVal));
    int httpCode = http.GET();
    Serial.println(httpCode);
    if (httpCode > 0)
      Serial.println("Delivered...");

    http.end();
  }

  delay(3000);
}

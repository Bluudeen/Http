#include <ESP8266WebServer.h>

#ifndef STASSID
#define STASSID "Merida 2.4GHz"
#define STAPSK  "71karel23"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80); 
unsigned long previousMillis = 0;
unsigned long  interval = 1000;
boolean activated = true;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(LED_BUILTIN, OUTPUT);
  server.begin();

  server.on("/", bruh); 
  server.on("/On", On); 
  server.on("/Off", Off); 
  server.on("/Speed", Speed); 
}

void loop() {
  server.handleClient();

  if(activated) {
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
  }
}

void bruh() { 
  server.send(200, "text/plain", "OK");
} 

void On() { 
  activated = true; 
  digitalWrite(LED_BUILTIN, LOW);
  server.send(200, "text/plain", "LED zapnuta, aktivuji interval blikání");
}

void Off() {
  activated = false; 
  digitalWrite(LED_BUILTIN, HIGH);
  server.send(200, "text/plain", "LED vypnuta, deaktivuji interval blikání");
}

void Speed() { 
  String speed = server.arg("value");
  interval = speed.toInt() * 1000;
  activated = true; 
  server.send(200, "text/plain", "Rychlost nastavena na " + speed + " sekund, aktivuji interval blikání");
}

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Merida 2.4GHz"
#define STAPSK  "71karel23"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while(client.connected()) {
      if (client.available()){
        String line = client.readStringUntil('\r');
        Serial.println(line);
        if (line.indexOf("GET /uptime") == 0) {
          long uptime = millis();
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/plain; charset=utf-8");
          client.println("Connection: close");
          client.println();
          client.println(convertSecondsToHMmSs(uptime/1000));
          break;
        }
      }
    }
    while(client.available()) {
      client.read();
    }
    client.stop();
  }
}

static String convertSecondsToHMmSs(long seconds) {
    long s = seconds % 60;
    long m = (seconds / 60) % 60;
    long h = (seconds / (60 * 60)) % 24;
    return ((String)h + ":" + m + ":" + s);
}

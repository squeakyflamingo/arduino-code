/*********
  Code for a button which performs GET-requests against a local server.
  All logic is reversed due to a normally closed (nc) switch.

  Board used: Wemos Lolin 32

  Code by Tim and Ivo.

  26.10.2020 - CC0
*********/
#include <WiFi.h>
#include <HTTPClient.h>

#define BUTTON_PIN 32

const char* ssid = "Quack!";
const char* password = "naknaknak";

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);
  
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Button has been pressed");
    HTTPClient http;
    http.setReuse(true);
    http.begin("http://192.168.43.125/api/set.php?team=1");
    
    int httpResponseCode = http.GET();
    
    if (httpResponseCode == 200) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  }
}

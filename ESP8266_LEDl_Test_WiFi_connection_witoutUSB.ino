#include <ESP8266WiFi.h>

const char* ssid     = "";     
const char* password = ""; 
const int LED_PIN = 5; 

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // 起動していることを確認（1秒点灯）
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    // 接続中（点滅）
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
  }

  // 接続完了（3回点滅）
  for(int i=0; i<3; i++){
    digitalWrite(LED_PIN, HIGH); delay(100);
    digitalWrite(LED_PIN, LOW);  delay(100);
  }

  Serial.println("\nWiFi Connected!");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '1') digitalWrite(LED_PIN, HIGH);
    else if (command == '0') digitalWrite(LED_PIN, LOW);
  }
}
#include <ESP8266WiFi.h>

const char* ssid     = "";     
const char* password = "";

const int LED_PIN = 5; 

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println();
  Serial.println("--- WiFi Connection Test Start ---");

  // 3. WiFi接続を開始
  WiFi.begin(ssid, password);

  // 4. 接続が完了するまでループして待つ
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // 待機中にドットを表示（進行状況の可視化）
  }

  // 5. 接続完了
  Serial.println("");
  Serial.println("WiFi Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // 割り当てられたIPを表示
  
  Serial.println("Ready to receive Serial commands ('1' or '0')");
}



void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == '1') {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED: [ ON ]");
    } 
    else if (command == '0') {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED: [ OFF ]");
    }
  }
}
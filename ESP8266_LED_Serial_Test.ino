// OSOYOOの「D1」ピンはGPIO5番です
const int LED_PIN = 5; 

void setup() {
  // LEDピンを出力モードに設定
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // 最初は消灯しておく

  // PCとのシリアル通信を開始（速度は115200を指定）
  Serial.begin(115200);
  delay(500);
  
  Serial.println("--- LED Control System Ready ---");
  Serial.println("Type '1' to ON, '0' to OFF");
}

void loop() {
  // PCからデータが送られてきたかチェック
  if (Serial.available() > 0) {
    char command = Serial.read(); // 届いた文字を1つ読み取る

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
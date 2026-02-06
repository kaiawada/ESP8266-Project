#include "DHT.h"
#define DHTPIN 2     
#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println(F("--- DHT22 疎通テスト開始 ---"));

  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("センサーからの読み取りに失敗しました。"));
    return;
  }

  Serial.print(F("湿度: "));
  Serial.print(h);
  Serial.print(F("%  温度: "));
  Serial.print(t);
  Serial.println(F("°C"));
}
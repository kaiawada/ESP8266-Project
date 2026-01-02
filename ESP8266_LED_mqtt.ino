#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* ssid     = "";
const char* password = "";
const char* mqtt_server = "broker.emqx.io";


const char* topic_cmnd = "kyberno/grc/pump001/cmnd";
const char* topic_stat = "kyberno/grc/pump001/stat";


const int RED_LED_PIN = 5; // D1ピン（将来のリレーIN）

WiFiClient espClient;
PubSubClient client(espClient);


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("MQTT Received [");
  Serial.print(topic);
  Serial.print("] ");


  char message = (char)payload[0];
  Serial.println(message);

  if (message == '1') {
    digitalWrite(RED_LED_PIN, HIGH);// 赤色LED消灯
    client.publish(topic_stat, "ON", true);
    Serial.println("Status: LED ON");
  } 
  else if (message == '0') {
    digitalWrite(RED_LED_PIN, LOW);// 赤色LED消灯
    client.publish(topic_stat, "OFF", true);
    Serial.println("Status: LED OFF");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("kyberno_grc_tester_001")) {
      Serial.println("connected");
      client.subscribe(topic_cmnd);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED_PIN, OUTPUT);

  digitalWrite(RED_LED_PIN, HIGH);
  delay(1000);
  digitalWrite(RED_LED_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
   
    digitalWrite(RED_LED_PIN, !digitalRead(RED_LED_PIN)); 
  }

  for(int i=0; i<5; i++){
    digitalWrite(RED_LED_PIN, HIGH); delay(200);
    digitalWrite(RED_LED_PIN, LOW);  delay(100);
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // MQTT設定
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); 
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

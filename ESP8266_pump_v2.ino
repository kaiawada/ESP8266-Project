#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* ssid     = "";
const char* password = "";
const char* mqtt_server = ""; 


const char* topic_cmnd = "Kyberno/grc/pump001/cmd";
const char* topic_stat = "Kyberno/grc/pump001/status";


const int RELAY_PIN   = D1;
const int RED_LED_PIN = D2;）
const int BLUE_LED_PIN = D3;

WiFiClient espClient;
PubSubClient client(espClient);


void callback(char* topic, byte* payload, unsigned int length) {
  
  digitalWrite(BLUE_LED_PIN, LOW);
  
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("MQTT Received [");
  Serial.print(topic);
  Serial.print("] Message: ");
  Serial.println(message);

  if (message == "ON") {
    digitalWrite(RELAY_PIN, HIGH);
    client.publish(topic_stat, "ON", true);
    Serial.println("Action: Pump ON");
  } 
  else if (message == "OFF") {
    digitalWrite(RELAY_PIN, LOW);
    client.publish(topic_stat, "OFF", true);
    Serial.println("Action: Pump OFF");
  }
  
  delay(100);
  digitalWrite(BLUE_LED_PIN, HIGH);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    digitalWrite(BLUE_LED_PIN, LOW);

    if (client.connect("kyberno_pump_client")) {
      Serial.println("connected");
      client.subscribe(topic_cmnd);
      digitalWrite(BLUE_LED_PIN, HIGH);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);

  
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(RED_LED_PIN, !digitalRead(RED_LED_PIN));
  }

  digitalWrite(RED_LED_PIN, HIGH);
  Serial.println("\nWiFi Connected!");

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); 
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
#include "mqtt.h"
#include "./beacon/beacon.h"


WiFiClient wifiClient;
PubSubClient mqttClient(RASP_BROKER_IP, PORTA, wifiClient);

void Mqtt::wifiConnect() {
  WiFi.begin(SSIDRASP, PASS);
  Serial.print("Conectando à rede WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println("Conectado à rede WiFi");
  WiFi.mode(WIFI_STA);
}


void Mqtt::mqtt(String nome_beacon, int frequencia) {
  if (mqttClient.connect(nome_servidor, MQTT_USER, MQTT_SENHA)) {
    Serial.println("Conectado ao broker MQTT");
  } else {
    Serial.println("Falha ao conectar ao broker MQTT");
  }

  if (mqttClient.connected()) {
    String topico = nome_beacon +","+ frequencia;
    mqttClient.publish(nome_servidor, topico.c_str());
  }
}

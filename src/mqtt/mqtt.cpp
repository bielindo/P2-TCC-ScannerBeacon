#include "mqtt.h"
#include "./beacon/beacon.h"

// Cria um objeto WiFiClient para gerenciar a conexão Wi-Fi
WiFiClient wifiClient;

// Cria um objeto PubSubClient para gerenciar a conexão MQTT, passando o endereço IP do Broker MQTT, a porta e o cliente WiFi
PubSubClient mqttClient(RASP_BROKER_IP, PORTA, wifiClient);

// Função para conectar o ESP32 à rede Wi-Fi
void Mqtt::wifiConnect() {
  // Verifica se o ESP32 já está conectado à rede Wi-Fi
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  // Inicia a conexão Wi-Fi com as credenciais definidas (SSIDRASP e PASS)
  WiFi.begin(SSIDRASP, PASS);
  Serial.println("Conectando à rede WiFi");

  // Espera pela conexão Wi-Fi ser estabelecida
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Não conectado ao WiFi");
    delay(2000);
    ESP.restart(); // Reinicia o ESP32 em caso de falha na conexão Wi-Fi
  }

  Serial.println("");
  Serial.println("Conectado à rede WiFi");
  WiFi.mode(WIFI_STA); // Configura o ESP32 para o modo cliente Wi-Fi
}

// Função para enviar uma mensagem via MQTT
void Mqtt::mqtt(String mensagem) {
  // Verifica se o ESP32 está conectado ao Broker MQTT
  if (mqttClient.connect(nome_servidor, MQTT_USER, MQTT_SENHA)) {
    Serial.println("Conectado ao broker MQTT");
  } else {
    Serial.println("Falha ao conectar ao broker MQTT");
  }

  // Verifica se a conexão MQTT está estabelecida
  if (mqttClient.connected()) {
    if (mensagem != "") {
      // Publica a mensagem no tópico definido pelo nome_servidor
      mqttClient.publish(nome_servidor, mensagem.c_str());
    }
  }
}

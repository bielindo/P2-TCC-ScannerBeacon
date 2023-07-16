#ifndef MQTT_H
#define MQTT_H

#include "./estrutura/estrutura.h"
#include <PubSubClient.h>
#include <WiFi.h>

// Define o nome da rede Wi-Fi e a senha para que o ESP32 se conecte
#define SSIDRASP "nome_wifi"
#define PASS "senha_wifi"

// Define o endereço IP e a porta do Broker MQTT
#define RASP_BROKER_IP "IP_BROKER"
#define PORTA 1883

// Define o nome de usuário e a senha para autenticação no MQTT
#define MQTT_USER "login_mqtt"
#define MQTT_SENHA "senha_mqtt"

extern WiFiClient wifiClient;
extern PubSubClient mqttClient;

class Mqtt {
public:

    // Função para conectar o ESP32 à rede Wi-Fi
    void wifiConnect();

    // Função para enviar uma mensagem via MQTT
    void mqtt(String mensagem);
};

#endif

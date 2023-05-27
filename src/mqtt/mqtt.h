#ifndef MQTT_H
#define MQTT_H

#include "./estrutura/estrutura.h"
#include <PubSubClient.h>
#include <WiFi.h>

//Define a o Wi-fi e a Senha que o esp ira se conectar
#define SSIDRASP "TCC-Gabriel"
#define PASS "tccGabriel"


//Define o IP e a porta do Broker para o MQTT
#define RASP_BROKER_IP "192.168.0.101"
#define PORTA 1883

#define MQTT_USER "TCC-Gabriel"
#define MQTT_SENHA "tccgabriel"

extern WiFiClient wifiClient;
extern PubSubClient mqttClient;


class Mqtt{
public:

    //Funcao para conectar o Wi-fi no esp
    void wifiConnect();
    void mqtt(String beacon[], int tamanho);
};

#endif
#ifndef BEACON_H
#define BEACON_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEBeacon.h>

// Declaração externa do mapa global que armazenará os dispositivos encontrados
extern std::map<std::string, std::vector<int>> devices;

// Classe Beacon: Responsável por escanear e coletar as informações dos beacons BLE
class Beacon {

public:
    int scanTime = 3; // Tempo de duração do escaneamento em segundos
    BLEScan *pBLEScan; // Ponteiro para o objeto de escaneamento BLE

    // Função para calcular e imprimir as médias das frequências RSSI dos dispositivos encontrados
    void calcularMedia();

    // Função para iniciar o escaneamento de beacons BLE
    void scanForBeacons();    
};

#endif

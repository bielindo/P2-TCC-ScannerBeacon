
#include "beacon.h"
#include "./estrutura/estrutura.h"
#include <iostream>
#include <string>
#include "./mqtt/mqtt.h"


Mqtt mqtt;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
public:
    std::vector<std::string> beacons; // Vetor de strings para armazenar os beacons
    
    void onResult(BLEAdvertisedDevice advertisedDevice) {
        if (advertisedDevice.haveName()) {
            Serial.println("-----------------------");
            Serial.print("Nome do dispositivo: ");
            Serial.println(advertisedDevice.getName().c_str());
            
            std::string nome_beacon = advertisedDevice.getName().c_str();
            
            Serial.print("RSSI: ");
            Serial.println(advertisedDevice.getRSSI());
            
            int frequencia = advertisedDevice.getRSSI();
            
            std::string beaconCompleto = nome_beacon + "," + std::to_string(frequencia) + ";";
            
            beacons.push_back(beaconCompleto); // Adiciona o beacon ao vetor
        }
    }
};


void Beacon::scanForBeacons() {
    BLEDevice::init(nome_servidor);
    pBLEScan = BLEDevice::getScan();
    auto callback = new MyAdvertisedDeviceCallbacks();
    pBLEScan->setAdvertisedDeviceCallbacks(callback);
    pBLEScan->setActiveScan(true);
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);
    Serial.println("DEMORA?");
    BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  
    pBLEScan->clearResults();
    
    mqtt.wifiConnect();
  
    size_t numBeacons = callback->beacons.size();
    String* beaconArray = new String[numBeacons];
    for (size_t i = 0; i < numBeacons; i++) {
      beaconArray[i] = callback->beacons[i].c_str();
    }

    mqtt.mqtt(beaconArray, numBeacons);

    delete[] beaconArray;
}



#include "beacon.h"
#include "./estrutura/estrutura.h"
#include "./mqtt/mqtt.h"


Mqtt mqtt;



class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  public: 
    String nome_beacon = "";
    int frequencia = 0;
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      if (advertisedDevice.haveName()) {
        if (!strcmp(advertisedDevice.getName().c_str(), "SegundoBeacon")) {
          Serial.println("-----------------------");
          Serial.print("Nome do dispositivo: ");
          Serial.println(advertisedDevice.getName().c_str());
          nome_beacon = advertisedDevice.getName().c_str();
          Serial.print("RSSI: ");
          Serial.println(advertisedDevice.getRSSI());
          frequencia = advertisedDevice.getRSSI();
          Serial.println("");
        }
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

  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);

  pBLEScan->clearResults();
  mqtt.wifiConnect();
  mqtt.mqtt(callback->nome_beacon, callback->frequencia);
}


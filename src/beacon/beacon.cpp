#include "beacon.h"
#include "./estrutura/estrutura.h"
#include "./mqtt/mqtt.h"


Mqtt mqtt;

std::map<std::string, std::vector<int>> devices;



class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    std::string deviceName = advertisedDevice.getName();

    // Verifica se o dispositivo possui um nome
    if (!deviceName.empty()) {
      // Verifica se o dispositivo já foi encontrado anteriormente
      if (devices.find(deviceName) == devices.end()) {
        devices[deviceName] = std::vector<int>();
      }

      // Obtém a frequência RSSI do dispositivo
      int rssi = advertisedDevice.getRSSI();

      // Armazena a frequência RSSI no vetor do dispositivo correspondente
      devices[deviceName].push_back(rssi);

      Serial.print("Device found: ");
      Serial.print(deviceName.c_str());
      Serial.print(" | RSSI: ");
      Serial.println(rssi);
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

    for (int i = 0; i < 10; i++) {
        BLEScanResults scanResults = pBLEScan->start(3, false);
        delay(1000);  // Aguarda 1 segundo antes de iniciar o próximo escaneamento
    }
    mqtt.wifiConnect();
    calculateAndPrintAverages();
    devices.clear();
}

void Beacon::calculateAndPrintAverages() {
  std::map<std::string, float> averages;
  String mensagem;

  for (const auto& device : devices) {
    std::string deviceName = device.first;
    const std::vector<int>& frequencies = device.second;

    int sum = 0;
    for (int frequency : frequencies) {
      sum += frequency;
    }

    float average = static_cast<float>(sum) / frequencies.size();
    averages[deviceName] = average;

    Serial.print("Device: ");
    Serial.print(deviceName.c_str());
    Serial.print(" | Average RSSI: ");
    Serial.println(average);

    mensagem += String(deviceName.c_str()) + ", " + String(average) + "; ";

    Serial.print("Frequencies: ");
    for (int frequency : frequencies) {
      Serial.print(frequency);
      Serial.print(" ");
    }
    Serial.println();
  }

  Serial.print("MENSAGEM: ");
  Serial.println(mensagem);
  mqtt.mqtt(mensagem);
}


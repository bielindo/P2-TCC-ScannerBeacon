#include "beacon.h"
#include "./estrutura/estrutura.h"
#include "./mqtt/mqtt.h"

Mqtt mqtt;

std::map<std::string, std::vector<int>> devices;

// Classe de Callbacks para dispositivos BLE encontrados durante o escaneamento
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

// Função para escanear e coletar as frequências RSSI dos dispositivos próximos (beacons)
void Beacon::scanForBeacons() {
    // Inicializa o módulo BLE com o nome do servidor fornecido
    BLEDevice::init(nome_servidor);

    // Obtém uma instância do objeto de escaneamento BLE
    pBLEScan = BLEDevice::getScan();

    // Configuração do callback personalizado para tratar dispositivos encontrados
    auto callback = new MyAdvertisedDeviceCallbacks();
    pBLEScan->setAdvertisedDeviceCallbacks(callback);

    // Configura o escaneamento BLE
    pBLEScan->setActiveScan(true);
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);

    // Executa o escaneamento 10 vezes com intervalos de 1 segundo entre eles
    for (int i = 0; i < 10; i++) {
        BLEScanResults scanResults = pBLEScan->start(3, false);
        delay(1000);  // Aguarda 1 segundo antes de iniciar o próximo escaneamento
    }

    // Conecta-se à rede Wi-Fi usando MQTT
    mqtt.wifiConnect();

    // Calcula e imprime as médias das frequências RSSI dos dispositivos encontrados
    calculateAndPrintAverages();

    // Limpa o mapa de dispositivos para a próxima execução
    devices.clear();
}

// Função para calcular e imprimir as médias das frequências RSSI dos dispositivos encontrados
void Beacon::calculateAndPrintAverages() {
  // Mapa para armazenar as médias calculadas das frequências RSSI
  std::map<std::string, float> averages;
  String mensagem;

  // Itera sobre o mapa de dispositivos encontrados
  for (const auto& device : devices) {
    std::string deviceName = device.first;
    const std::vector<int>& frequencies = device.second;

    int sum = 0;
    // Calcula a soma das frequências RSSI do dispositivo atual
    for (int frequency : frequencies) {
      sum += frequency;
    }

    // Calcula a média das frequências RSSI do dispositivo atual
    float average = static_cast<float>(sum) / frequencies.size();
    averages[deviceName] = average;

    // Imprime as informações do dispositivo e sua média RSSI
    Serial.print("Device: ");
    Serial.print(deviceName.c_str());
    Serial.print(" | Average RSSI: ");
    Serial.println(average);

    // Constrói a mensagem a ser enviada via MQTT
    mensagem += String(deviceName.c_str()) + ", " + String(average) + "; ";

    // Imprime as frequências RSSI individuais do dispositivo
    Serial.print("Frequencies: ");
    for (int frequency : frequencies) {
      Serial.print(frequency);
      Serial.print(" ");
    }
    Serial.println();
  }

  // Imprime a mensagem a ser enviada via MQTT
  Serial.print("MENSAGEM: ");
  Serial.println(mensagem);

  // Envia a mensagem via MQTT
  mqtt.mqtt(mensagem);
}

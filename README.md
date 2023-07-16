# Beacon Scanner

Este é um aplicativo para escanear e coletar informações de beacons Bluetooth Low Energy (BLE) próximos usando o módulo BLE do Arduino.

## Instalação

1. Clone este repositório para o seu ambiente de desenvolvimento local.

    git clone https://github.com/bielindoo/beacon-scanner.git
    cd beacon-scanner



1. Certifique-se de ter a biblioteca ArduinoBLE instalada. Se você ainda não a tiver, pode instalá-la usando o Library Manager do Arduino IDE.

2. Conecte seu dispositivo Arduino com módulo BLE.

3. Abra o arquivo beacon-scanner.ino usando a Arduino IDE.

4. Carregue o código no seu dispositivo Arduino.


## Como Usar

O aplicativo Beacon Scanner escaneará os dispositivos BLE próximos e coletará suas frequências RSSI. Ele calculará as médias das frequências RSSI dos dispositivos encontrados e enviará os resultados através do protocolo MQTT para um servidor.

Para usar o aplicativo, siga os passos abaixo:

1. Conecte o dispositivo Arduino com módulo BLE e inicie o programa.

2. O aplicativo começará a escanear beacons próximos e exibirá os dispositivos encontrados na saída Serial.

3. Após o escaneamento, ele se conectará à rede Wi-Fi através do protocolo MQTT.

4. As médias das frequências RSSI dos dispositivos encontrados serão calculadas e enviadas via MQTT para um servidor.

## Configuração

Você pode configurar o tempo de duração do escaneamento e outras opções no arquivo `beacon.h`.

## Dependencias

- [ArduinoBLE](https://www.arduino.cc/en/Reference/ArduinoBLE): Biblioteca para o módulo BLE do Arduino.

- [PubSubClient](https://github.com/knolleary/pubsubclient): Biblioteca para comunicação MQTT.


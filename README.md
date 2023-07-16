# P2 - Projeto TCC (Sistema de monitoramento e rastreamento de objetos indoor) - Beacon Scanner

Este é o segundo repositório do projeto de Trabalho de Conclusão de Curso (TCC) sobre localização indoor, intitulado "Scanner Beacon". O objetivo deste projeto é escanear e coletar informações de beacons Bluetooth Low Energy (BLE) próximos usando o módulo BLE do ESP32.

## Instalação

1. Clone este repositório para o seu ambiente de desenvolvimento local.

    git clone [git@github.com:bielindo/tccScannerBeacon.git](https://github.com/bielindo/tccScannerBeacon.git)
   
    cd beacon-scanner



2. Certifique-se de ter a biblioteca ArduinoBLE instalada. Se você ainda não a tiver, pode instalá-la usando o Library Manager do Arduino IDE ou, se estiver usando a plataforma PlatformIO, as bibliotecas são gerenciadas automaticamente.

3. Certifique - se que o seu dispositivo ESP32 possua um módulo BLE.

4. Abra o arquivo beacon-scanner.ino usando a Arduino IDE ou a plataforma PlatformIO.

5. Carregue o código no seu dispositivo ESP32.


## Como Usar

O aplicativo Beacon Scanner escaneará os dispositivos BLE próximos e coletará suas frequências RSSI. Ele calculará as médias das frequências RSSI dos dispositivos encontrados e enviará os resultados através do protocolo MQTT para um servidor.

Para usar o aplicativo, siga os passos abaixo:

1. Conecte o dispositivo ESP32 com módulo BLE e inicie o programa.

2. O aplicativo começará a escanear beacons próximos e exibirá os dispositivos encontrados na saída Serial.

3. Após o escaneamento, ele se conectará à rede Wi-Fi através do protocolo MQTT.

4. As médias das frequências RSSI dos dispositivos encontrados serão calculadas e enviadas via MQTT para um servidor.

## Configuração

Você pode configurar o tempo de duração do escaneamento e outras opções no arquivo `beacon.h`.

## Dependencias

- [ArduinoBLE](https://www.arduino.cc/en/Reference/ArduinoBLE): Biblioteca para o módulo BLE do Arduino.

- [PubSubClient](https://github.com/knolleary/pubsubclient): Biblioteca para comunicação MQTT.

## Licença

Este projeto está sob a licença MIT. Consulte o arquivo LICENSE para obter mais detalhes.


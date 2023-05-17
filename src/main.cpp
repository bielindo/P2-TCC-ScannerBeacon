#include <Arduino.h>
#include "beacon/beacon.h"
#include "mqtt/mqtt.h"

Beacon beacon;

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Varrendo beacons...");
  beacon.scanForBeacons();
  delay(5000);
}
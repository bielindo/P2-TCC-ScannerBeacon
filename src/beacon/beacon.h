#ifndef BEACON_H
#define BEACON_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEBeacon.h>

extern std::map<std::string, std::vector<int>> devices;

class Beacon{

public:
    int scanTime = 3;
    BLEScan *pBLEScan;
    void calculateAndPrintAverages();
    void scanForBeacons();    
};



#endif

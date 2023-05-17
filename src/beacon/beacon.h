#ifndef BEACON_H
#define BEACON_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEBeacon.h>


class Beacon{

public:
    int scanTime = 10;
    BLEScan *pBLEScan;

    void scanForBeacons();
        
};


#endif

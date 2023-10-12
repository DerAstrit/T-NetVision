#pragma once
#include <vector>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEEddystoneURL.h>
#include <BLEEddystoneTLM.h>
#include <BLEBeacon.h>
#include <Arduino.h> 
#include "BeaconData.h"

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
public:
    std::vector<BeaconData> detectedBeacons;
    void onResult(BLEAdvertisedDevice advertisedDevice);
};

class BLEScanner
{
public:
    BLEScanner();
    void init();
    std::vector<BeaconData> scan();
private:
    BLEScan* pBLEScan;
    MyAdvertisedDeviceCallbacks* pAdvertisedDeviceCallbacks;
};

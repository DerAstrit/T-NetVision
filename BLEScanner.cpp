#include "BLEScanner.h"

BLEScanner::BLEScanner()
{
    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan();
    pAdvertisedDeviceCallbacks = new MyAdvertisedDeviceCallbacks();
    pBLEScan->setAdvertisedDeviceCallbacks(pAdvertisedDeviceCallbacks);
    pBLEScan->setActiveScan(true);
}

void BLEScanner::init()
{
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);
}

std::vector<BeaconData> BLEScanner::scan()
{
    pBLEScan->start(5, false);
    pBLEScan->clearResults(); // Clear results from BLEScan buffer to release memory
    return pAdvertisedDeviceCallbacks->detectedBeacons;
}

void MyAdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice)
{
    BeaconData beaconData;
    beaconData.RSSI = advertisedDevice.getRSSI();

    // Check for iBeacon and get its data
    if (advertisedDevice.haveManufacturerData())
    {
        std::string manData = advertisedDevice.getManufacturerData();
        if (manData.size() == 25 && static_cast<uint8_t>(manData[0]) == 0x4C && static_cast<uint8_t>(manData[1]) == 0x00)
        {
            BLEBeacon oBeacon = BLEBeacon();
            oBeacon.setData(manData);
            beaconData.major = oBeacon.getMajor();
            beaconData.minor = oBeacon.getMinor();
            detectedBeacons.push_back(beaconData);
            return;
        }
    }

    // Check for Eddystone and get its data
    if (advertisedDevice.haveServiceData() && advertisedDevice.isAdvertisingService(BLEUUID((uint16_t)0xFEAA)))
    {
        std::string serviceData = advertisedDevice.getServiceData();
        uint8_t firstByte = static_cast<uint8_t>(serviceData[0]);
        if (firstByte == 0x10) // Eddystone URL
        {
            BLEEddystoneURL eddyURL = BLEEddystoneURL();
            eddyURL.setData(serviceData);
            detectedBeacons.push_back(beaconData);
        }
        else if (firstByte == 0x20) // Eddystone TLM
        {
            BLEEddystoneTLM eddyTLM = BLEEddystoneTLM();
            eddyTLM.setData(serviceData);
            detectedBeacons.push_back(beaconData);
        }
        return;
    }

    // If no known beacon types were detected
    detectedBeacons.push_back(beaconData);
}


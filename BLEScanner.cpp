#include "BLEScanner.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <vector>
#include "DeviceConstants.h"

std::vector<BeaconData> BLEScanner::scan()
{
    // Initialize BLE for scanning
    BLEDevice::init("");
    BLEScan *pBLEScan = BLEDevice::getScan();
    pBLEScan->setActiveScan(true);

    // Start scanning for BLE devices for the specified duration
    BLEScanResults foundDevices = pBLEScan->start(BLE_SCAN_DURATION, false);

    std::vector<BeaconData> detectedBeacons;

    // Loop through all found devices
    for (int i = 0; i < foundDevices.getCount(); i++)
    {
        BLEAdvertisedDevice device = foundDevices.getDevice(i);

        // Check if the device has manufacturer data of the expected length
        // Expected data format: <2 bytes header><16 bytes UUID><2 bytes Major><2 bytes Minor><1 byte RSSI>
        std::string manufacturerData = device.getManufacturerData();
        if (device.haveManufacturerData() && manufacturerData.length() == 23)
        {
            std::string uuid = manufacturerData.substr(2, 16);
            int major = manufacturerData[18] * 256 + manufacturerData[19];
            int minor = manufacturerData[20] * 256 + manufacturerData[21];

            BeaconData beaconData;
            beaconData.UUID = uuid.c_str(); // Convert std::string to Arduino String
            beaconData.major = major;
            beaconData.minor = minor;
            beaconData.RSSI = device.getRSSI();

            // Add the beacon data to the list of detected beacons
            detectedBeacons.push_back(beaconData);
        }
    }

    pBLEScan->stop(); // Stop scanning

    return detectedBeacons; // Return the list of detected beacons
}

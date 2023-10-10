#pragma once
#include <vector>
#include "BeaconData.h"

// Class to handle BLE scanning operations
class BLEScanner
{
public:
    // Method to scan for BLE beacons and return a vector containing their data
    std::vector<BeaconData> scan();
};

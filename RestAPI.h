#pragma once
#include <vector>
#include "BeaconData.h"

class RestAPI
{
public:
    // Method to post collected beacon data, GPS coordinates, and IMEI to the server
    // Returns the HTTP response code
    int post(std::vector<BeaconData> beacons, float latitude, float longitude, String IMEI);
};

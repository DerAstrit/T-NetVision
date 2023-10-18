#pragma once
#include <vector>
#include "BeaconData.h"

class RestAPI
{
public:
    int post(const std::vector<BeaconData>& beacons, float latitude, float longitude, const String& IMEI);
};

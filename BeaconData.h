#pragma once
#include <Arduino.h>

struct BeaconData
{
    String UUID;        // Unique identifier for the beacon
    int16_t major;      // Group identifier for a subset of beacons
    int16_t minor;      // Identifier for an individual beacon within a group
    int8_t RSSI;        // Signal strength of the beacon
    int8_t batteryLevel;// Battery level of the beacon, if available
    
    // Optional members, add if needed:
    // String type;      // Type of beacon (e.g., iBeacon, Eddystone)
    // String uuid_or_url;// Either the UUID or a URL, depending on beacon type
    // int8_t txPower;   // Transmit power of the beacon
};

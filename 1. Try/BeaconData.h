#pragma once
#include <Arduino.h>

struct BeaconData
{
    String UUID;        // Unique identifier for the beacon, in standard UUID format.
    int16_t major;      // Group identifier for a subset of beacons, expected: non-negative integer.
    int16_t minor;      // Identifier for an individual beacon within a group, expected: non-negative integer.
    int8_t RSSI;        // Signal strength of the beacon in dBm, expected: typically a negative value, the closer to 0, the stronger the signal.
    int8_t batteryLevel;// Battery level of the beacon in percentage, if available, expected: [0, 100]. -1 indicates unavailable.

    // Optional members, add if needed:
    // String type;      // Type of beacon (e.g., iBeacon, Eddystone)
    // String uuid_or_url;// Either the UUID or a URL, depending on beacon type
    // int8_t txPower;   // Transmit power of the beacon
};

#pragma once
#include <Arduino.h>

struct BeaconData
{
    String UUID;           // UUID of the beacon
    int16_t major;         // Major value for iBeacon. Typical range: 0-65535
    int16_t minor;         // Minor value for iBeacon. Typical range: 0-65535
    int8_t RSSI;           // Received Signal Strength Indication. Typical range: -127 to +20 dBm
    int8_t batteryLevel;   // Battery level of the beacon (if available). Range: 0-100 (%)
};

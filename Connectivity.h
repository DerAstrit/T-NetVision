#pragma once
#include <Arduino.h>
#include "DeviceConstants.h"

// Class to handle communication and interaction with the modem for GPRS and GPS functionality
class Connectivity
{
public:
    // Constructor to initialize the modem communication
    Connectivity();

    // Method to establish a GPRS connection
    void connectGPRS();

    // Method to check the status of the GPRS connection
    bool isGprsConnected();

    // Method to start the GPS
    void startGPS();

    // Method to retrieve the current GPS coordinates
    void getGPSLocation(float &latitude, float &longitude);

    // Method to stop the GPS
    void stopGPS();

    // Method to retrieve the device's IMEI
    String getIMEI();
};

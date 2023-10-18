#pragma once
#include "Arduino.h"

#define TINY_GSM_MODEM_SIM7000
#include <TinyGsmClient.h>

class Connectivity {
public:
    Connectivity();
    void init();
    void connectToNetwork();
    void checkNetworkStatus();
    void getNetworkParameters();
private:
    TinyGsm modem;
};

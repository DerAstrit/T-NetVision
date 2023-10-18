#include "Connectivity.h"

Connectivity::Connectivity() : modem(Serial1) {}

void Connectivity::init() {
    Serial1.begin(9600);
    modem.restart();
}

void Connectivity::connectToNetwork() {
    Serial.println("Connecting to network...");
    modem.init();
    String modemInfo = modem.getModemInfo();
    Serial.print("Modem: ");
    Serial.println(modemInfo);

    // Unlock your SIM card with a PIN
    modem.simUnlock("8671");

    Serial.print("Waiting for network...");
    if (!modem.waitForNetwork()) {
        Serial.println(" fail");
        delay(10000);
        return;
    }
    Serial.println(" OK");
}

void Connectivity::checkNetworkStatus() {
    Serial.print("Network status: ");
    if (modem.isNetworkConnected()) {
        Serial.println("connected");
    } else {
        Serial.println("disconnected");
    }
}

void Connectivity::getNetworkParameters() {
    String ccid = modem.getSimCCID();
    Serial.print("CCID: ");
    Serial.println(ccid);

    String imei = modem.getIMEI();
    Serial.print("IMEI: ");
    Serial.println(imei);

    String imsi = modem.getIMSI();
    Serial.print("IMSI: ");
    Serial.println(imsi);
}

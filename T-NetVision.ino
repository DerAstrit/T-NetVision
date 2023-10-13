#include "BLEScanner.h"
#include "RestAPI.h"
#include "DeviceConstants.h"
#include "Connectivity.h"

BLEScanner scanner;
RestAPI api;
Connectivity connection;
String imei;  // Global storage for IMEI

void setup()
{   
    initSerialCommunication();
    if(!Serial) return;
    readAndPrintIMEI();
    if(imei == "") return;
    Serial.println("initGPRSConnection");
    initGPRSConnection();
    if(!connection.isGprsConnected()) return;
    Serial.println("initGPS");
    initGPS();
}

void loop()
{
    static unsigned long lastPostTime = 0;  // Speichert den letzten Zeitpunkt der Datenübertragung

    // Überprüft, ob seit dem letzten Post POST_INTERVAL vergangen ist
    if (millis() - lastPostTime >= POST_INTERVAL) {
        float latitude, longitude;
        connection.getGPSLocation(latitude, longitude);

        // Scannt nach BLE Beacons
        std::vector<BeaconData> beacons = scanner.scan();

        // Sendet die gesammelten Daten an den Server
        api.post(beacons, latitude, longitude, imei);

        lastPostTime = millis();  // Aktualisiert den letzten Zeitpunkt der Datenübertragung
    }
}

void initSerialCommunication()
{
    Serial.begin(9600); // Start serial communication for debugging purposes
    Serial.println("initSerialCommunication");
}

void readAndPrintIMEI()
{
    Serial.println("Reading IMEI...");
    imei = connection.getIMEI();  // Fetch IMEI once and store it
    Serial.println("IMEI: " + imei);
}

void initGPRSConnection()
{
    connection.connectGPRS();

    // Check the GPRS connection status and provide feedback via the serial interface
    if (connection.isGprsConnected())
    {
        Serial.println("GPRS connected");
    }
    else
    {
        Serial.println("GPRS not connected");
        // Additional steps or reconnection attempts could be inserted here
    }
}

void initGPS()
{
    Serial.println("initGPS");
    connection.startGPS();
}

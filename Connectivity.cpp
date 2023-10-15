#include "Connectivity.h"
#include <TinyGsmClient.h>
#include <Arduino.h>
#include "DeviceConstants.h"

TinyGsm modem(Serial);

Connectivity::Connectivity() 
{
    // Initialize serial communication with the modem using the defined baud rate
    Serial.begin(MODEM_BAUD_RATE);
    delay(3000);  // Wait for the module to start up
}

void Connectivity::connectGPRS() 
{
    // Attempt to establish a GPRS connection
    
    // Unlock the SIM card with the PIN
    modem.simUnlock(GSM_PIN);
    
    if (!modem.gprsConnect(APN, GPRS_USER, GPRS_PASS)) 
    {
        Serial.println("Failed to connect to GPRS on first attempt.");
        int attempts = 3;
        while(attempts--)
        {
            delay(5000);  // Wait 5 seconds before retrying
            if(modem.gprsConnect(APN, GPRS_USER, GPRS_PASS))
            {
                Serial.println("Connected to GPRS on retry");
                return;
            }
        }
        Serial.println("Failed to connect to GPRS after multiple attempts");
        delay(60000);  // Sleep for 1 minute
        return;
    }
    Serial.println("Connected to GPRS");
}


bool Connectivity::isGprsConnected()
{
    // Check the status of the GPRS connection
    return modem.isGprsConnected();
}

void Connectivity::startGPS() 
{
    modem.sendAT("+CGNSPWR=1");
    if (modem.waitResponse() != 1) 
    {
        Serial.println("Failed to start GPS.");
        return;
    }
    Serial.println("GPS started");
}

void Connectivity::getGPSLocation(float &latitude, float &longitude) 
{
    modem.sendAT("+CGNSINF");
    String res;
    if (modem.waitResponse(10000L, res) != 1) 
    {
        Serial.println("Failed to get GPS data.");
        return;
    }

    // Parsing the response
    int index1 = res.indexOf(",") + 1; // Skip GNSS mode
    int index2 = res.indexOf(",", index1) + 1; // Skip GNSS fix status
    latitude = res.substring(index2, res.indexOf(",", index2)).toFloat();

    index1 = res.indexOf(",", index2) + 1;
    longitude = res.substring(index1, res.indexOf(",", index1)).toFloat();

    Serial.print("Latitude: ");
    Serial.println(latitude, 6);
    Serial.print("Longitude: ");
    Serial.println(longitude, 6);
}


void Connectivity::stopGPS()
{
    modem.sendAT("+CGNSPWR=0");
    if (modem.waitResponse() != 1) 
    {
        Serial.println("Failed to stop GPS.");
        return;
    }
    Serial.println("GPS stopped");
}

String Connectivity::getIMEI()
{
    // Retrieve the IMEI of the device
    return modem.getIMEI();
}

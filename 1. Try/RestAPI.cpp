#include "RestAPI.h"
#include "DeviceConstants.h"
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

int RestAPI::post(const std::vector<BeaconData>& beacons, float latitude, float longitude, const String& IMEI)
{
    Serial.println("Starting post function...");

    // Calculate the approximate size needed for the JSON object
    size_t jsonSize = JSON_OBJECT_SIZE(5) + JSON_ARRAY_SIZE(beacons.size()) * JSON_OBJECT_SIZE(3);

    // Create the JSON object using ArduinoJson library
    DynamicJsonDocument doc(jsonSize);
    doc["Device_Identifier"] = IMEI;
    doc["GPS_Latitude"] = latitude;
    doc["GPS_Longitude"] = longitude;
    doc["Tenant_ID"] = TENANT_ID;

    JsonArray beaconsArray = doc.createNestedArray("Beacons");
    for (const BeaconData& beacon : beacons)
    {
        if(beacon.RSSI > RSSI_THRESHOLD) // Only include beacons with RSSI above the threshold
        {
            JsonObject beaconObj = beaconsArray.createNestedObject();
            beaconObj["UUID"] = beacon.UUID;
            beaconObj["Major"] = beacon.major;
            beaconObj["Minor"] = beacon.minor;
            beaconObj["BatteryLevel"] = beacon.batteryLevel;
        }
    }

    String postData;
    serializeJson(doc, postData);
    Serial.println("JSON created: " + postData);

    // HTTP logic: Create the HTTP client and configure the request
    HTTPClient http;
    http.begin(REST_API_URL);  // Set the URL
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(postData);  // Send the POST request
    Serial.println("POST request sent. Response code: " + String(httpResponseCode));

    if (httpResponseCode > 0)
    {
        String response = http.getString();  // Get the response to the request
        Serial.println(httpResponseCode);    // Print the response code
        Serial.println(response);            // Print the response
    }
    else
    {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }
    http.end();  // Release resources

    return httpResponseCode;
}

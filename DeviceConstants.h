
#define TINY_GSM_MODEM_SIM800
#define SIM_PIN "8671"

#pragma once

// RSSI threshold for beacon detection
const int RSSI_THRESHOLD = -70;

// Time interval for posting data to the server (in milliseconds)
const int POST_INTERVAL = 30000;

// GPRS connection credentials
const char APN[] = "gprs.swisscom.ch";  // Access Point Name
const char GPRS_USER[] = "gprs";    // GPRS username
const char GPRS_PASS[] = "gprs";    // GPRS password

// API endpoint URL for data posting
const char URL[] = "https://personal-sl7oglgl.outsystemscloud.com";

// Subdomain (if any) for the API endpoint
const char SUBDOMAIN[] = "/TNetVision_API/rest/Lilygo_7080g/Post_Data";

// Duration for BLE scanning (in seconds)
const int BLE_SCAN_DURATION = 10;

// Baud rate for modem communication
const int MODEM_BAUD_RATE = 9600;

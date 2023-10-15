#pragma once

// Constants related to HTTP / REST API
const char* const REST_API_URL = "https://personal-sl7oglgl.outsystemscloud.com/TNetVision_API/rest/Lilygo_7080g/Post_Data";

// Constants related to GSM / Network
#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_USE_GPRS true
#define TINY_GSM_USE_WIFI false
const char* const GSM_PIN = "8671";
const char* const APN = "gprs.swisscom.ch";
const char* const GPRS_USER = "gprs";
const char* const GPRS_PASS = "gprs";

// Beacon RSSI Threshold
const int RSSI_THRESHOLD = -70; 
const char* const TENANT_ID = "YourTenantID"; 

// Time interval for posting data to the server (in milliseconds)
const int POST_INTERVAL = 30000;

// Duration for BLE scanning (in seconds)
const int BLE_SCAN_DURATION = 10;

// Baud rate for modem communication
const int MODEM_BAUD_RATE = 115200;

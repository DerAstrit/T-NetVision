#define TINY_GSM_MODEM_SIM800

#pragma once

// RSSI threshold for beacon detection
const int RSSI_THRESHOLD = -70;

// Time interval for posting data to the server (in milliseconds)
const int POST_INTERVAL = 30000;

// GPRS connection credentials
const char APN[] = "net2.vodafone.pt";  // Access Point Name
const char GPRS_USER[] = "vodafone";    // GPRS username
const char GPRS_PASS[] = "vodafone";    // GPRS password

// API endpoint URL for data posting
const char URL[] = "your_url_here";

// Subdomain (if any) for the API endpoint
const char SUBDOMAIN[] = "your_subdomain_here";

// Duration for BLE scanning (in seconds)
const int BLE_SCAN_DURATION = 10;

// Baud rate for modem communication
const int MODEM_BAUD_RATE = 9600;

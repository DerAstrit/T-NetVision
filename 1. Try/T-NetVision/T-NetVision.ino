#include "DeviceConstants.h"
#include "Connectivity.h"

Connectivity connectivity;

void setup() {
  initSerialCommunication();

    connectivity.init();
    connectivity.connectToNetwork();
}

void loop() {
  
    connectivity.checkNetworkStatus();
    delay(1000);

  Serial.println("loop...");

}








void initSerialCommunication()
{
    Serial.begin(MODEM_BAUD_RATE); // Start serial communication for debugging purposes
    Serial.println("initSerialCommunication started...");
}



void setup() {
  initSerialCommunication();
}

void loop() {
  // Leer lassen für den ersten Schritt
}

void initSerialCommunication() {
  Serial.begin(115200);
  delay(10);
  Serial.println("initSerialCommunication");
}

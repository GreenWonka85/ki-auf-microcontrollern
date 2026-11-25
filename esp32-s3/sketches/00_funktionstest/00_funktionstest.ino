// Sketch 0: Funktionstest fuer den ESP32-S3
// Gibt Chipmodell, Flash-Groesse und PSRAM im seriellen Monitor aus (115200 Baud).
// Hinweis: noch nicht auf echter Hardware getestet.

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.printf("Chip: %s, %d Kerne, %d MHz\n", ESP.getChipModel(), ESP.getChipCores(), ESP.getCpuFreqMHz());
  Serial.printf("Flash: %u MB\n", ESP.getFlashChipSize() / (1024 * 1024));
  Serial.printf("PSRAM gefunden: %s, Groesse: %u KB\n", psramFound() ? "ja" : "nein", ESP.getPsramSize() / 1024);
}

void loop() {}

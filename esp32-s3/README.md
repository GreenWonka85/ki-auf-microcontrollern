# Einstieg TinyML mit dem ESP32-S3

Diese Anleitung führt von der Installation bis zum ersten eigenen KI-Modell auf dem ESP32-S3: Arduino IDE 2, ESP32-S3 mit PSRAM und Edge Impulse. Zur Auswahl von IDE und Board siehe [Grundlagen](../grundlagen/).

> **Hinweis:** Die Sketches wurden noch nicht auf echter Hardware getestet. Sie liegen zusätzlich als `.ino`-Dateien im Ordner [sketches/](sketches/).

## Inhalt

- [Installation Schritt für Schritt](#installation-schritt-für-schritt)
- [Schnupperprojekt: Bewegungserkennung mit MPU6050](#schnupperprojekt-bewegungserkennung-mit-mpu6050)
- [Fehlersuche](#fehlersuche)
- [Nächste Schritte](#nächste-schritte)
- [Quellen](#quellen)

## Installation Schritt für Schritt

Du brauchst drei Dinge: die Arduino IDE mit ESP32-Boardpaket, ein kostenloses Edge-Impulse-Konto und die Edge Impulse CLI zum Übertragen der Sensordaten. Zeitaufwand etwa 30 Minuten.

### 1. Arduino IDE installieren

1. Die aktuelle Arduino IDE 2 von [arduino.cc/en/software](https://www.arduino.cc/en/software) laden. Stand November 2026 ist das Version 2.3.10 (veröffentlicht am 9. Juni 2026).
2. Installieren und starten. Unter Windows die Treiber-Abfragen bestätigen.
3. Falls eine ältere Arduino IDE 1.8 vorhanden ist: Sie kann parallel bleiben, Bibliotheken werden gemeinsam genutzt.

### 2. ESP32-Boardpaket installieren

1. **Datei > Einstellungen** öffnen. Unter "Zusätzliche Boardverwalter-URLs" eintragen: `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
2. **Werkzeuge > Board > Boardverwalter** öffnen, nach "esp32" suchen.
3. Das Paket **"esp32 by Espressif Systems"** installieren (nicht "Arduino ESP32 Boards"). Empfohlen ist die neueste 3.3.x-Version.
4. Hinweis zur Version: Edge Impulse testet offiziell noch mit dem alten Core 2.0.4, Exporte ab etwa Anfang 2025 laufen aber laut Edge-Impulse-Forum auch mit Core 3.x. Falls beim Kompilieren der Fehler `either all initializer clauses should be designated or none of them should be` erscheint, im Boardverwalter auf eine ältere Version wechseln (zuerst 3.1.x, notfalls 2.0.17).

### 3. Board und PSRAM einstellen

Board über USB anschließen. Das ESP32-S3-DevKitC-1 hat zwei Buchsen: **"UART"** (USB-Seriell-Wandler) und **"USB"** (nativer USB-Port). Für den Anfang die UART-Buchse nehmen, dann klappt der serielle Monitor ohne Sonderfall.

Unter **Werkzeuge** einstellen:

| Einstellung | ESP32-S3-DevKitC-1 N16R8 / N8R8 | Seeed XIAO ESP32S3 (Sense) |
| --- | --- | --- |
| Board | ESP32S3 Dev Module | XIAO_ESP32S3 |
| PSRAM | **OPI PSRAM** | **OPI PSRAM** |
| Flash Size | 16MB (128Mb) bzw. 8MB (64Mb) | 8MB (64Mb) |
| Partition Scheme | 16M Flash (3MB APP/9.9MB FATFS) bzw. 8M with spiffs (3MB APP/1.5MB SPIFFS) | Default with spiffs (3MB APP/1.5MB SPIFFS) |
| USB CDC On Boot | Disabled (UART-Buchse) / Enabled (USB-Buchse) | Enabled |
| Upload Speed | 921600 | 921600 |
| Port | der neue COM- bzw. /dev/ttyUSB-Port | der neue Port |

Zum PSRAM: Module mit **R8** (8 MB) nutzen Octal-PSRAM, daher "OPI PSRAM". Module mit **R2** (2 MB) nutzen Quad-PSRAM, dort "QSPI PSRAM" wählen. Bei falscher Einstellung startet das Board in einer Neustart-Schleife oder meldet keinen PSRAM. Bei Octal-PSRAM sind GPIO 35, 36 und 37 belegt und dürfen nicht verwendet werden.

### 4. Funktionstest

Den Sketch [00_funktionstest](sketches/00_funktionstest/00_funktionstest.ino) hochladen, seriellen Monitor auf 115200 Baud stellen. Erwartet werden etwa 8 MB PSRAM.

```cpp
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.printf("Chip: %s, %d Kerne, %d MHz\n", ESP.getChipModel(), ESP.getChipCores(), ESP.getCpuFreqMHz());
  Serial.printf("Flash: %u MB\n", ESP.getFlashChipSize() / (1024 * 1024));
  Serial.printf("PSRAM gefunden: %s, Groesse: %u KB\n", psramFound() ? "ja" : "nein", ESP.getPsramSize() / 1024);
}

void loop() {}
```

Falls der Upload hängt: BOOT-Taste gedrückt halten, kurz RST drücken, BOOT loslassen und erneut hochladen.

### 5. Edge Impulse vorbereiten

1. Kostenloses Konto auf [edgeimpulse.com](https://edgeimpulse.com) anlegen und ein neues Projekt erstellen, zum Beispiel "bewegung-esp32s3".
2. [Node.js](https://nodejs.org) in der aktuellen LTS-Version installieren.
3. Im Terminal (Windows: Eingabeaufforderung als normaler Benutzer) die CLI installieren: `npm install -g edge-impulse-cli`
4. Prüfen mit `edge-impulse-data-forwarder --version`. Die CLI liest später die Sensorwerte vom seriellen Port und lädt sie in dein Projekt.

## Schnupperprojekt: Bewegungserkennung mit MPU6050

Der ESP32-S3 erkennt am Beschleunigungssensor vier Zustände: **ruhe** (liegt still), **schuetteln**, **kreisen** und **sonstiges** (beliebiges Hantieren, Hintergrundklasse). Das klappt ohne zusätzliche Hardware am Schreibtisch und ist derselbe Ablauf wie später bei einer Lüfterüberwachung, nur mit anderen Klassen. Aufwand etwa 1,5 Stunden.

### Material

- ESP32-S3-DevKitC-1 (oder XIAO ESP32S3)
- MPU6050-Modul (GY-521)
- Steckbrett, 4 Jumperkabel, USB-Kabel

### Verdrahtung

| MPU6050 (GY-521) | ESP32-S3-DevKitC-1 | XIAO ESP32S3 |
| --- | --- | --- |
| VCC | 3V3 | 3V3 |
| GND | GND | GND |
| SDA | GPIO 8 | D4 (GPIO 5) |
| SCL | GPIO 9 | D5 (GPIO 6) |
| AD0 | GND (Adresse 0x68) | GND |
| INT | nicht belegt | nicht belegt |

Das GY-521 hat eigene Pull-up-Widerstände, zusätzliche sind nicht nötig. Das Modul fest auf dem Steckbrett fixieren, damit sich der Sensor beim Bewegen nicht lockert. Beim XIAO im Code `SDA_PIN 5` und `SCL_PIN 6` setzen.

### Schritt 1: Datenaufnahme-Sketch

Der Sketch [01_datenaufnahme_mpu6050](sketches/01_datenaufnahme_mpu6050/01_datenaufnahme_mpu6050.ino) liest den Sensor direkt über I2C (keine zusätzliche Bibliothek nötig) und gibt 100 Mal pro Sekunde die drei Achsen in m/s² aus, kommagetrennt. Genau dieses Format erwartet der Edge Impulse Data Forwarder.

Nach dem Hochladen kurz im seriellen Monitor prüfen: Liegt das Board flach, zeigt die Z-Achse etwa 9,8. Danach den **seriellen Monitor schließen**, sonst kann die CLI den Port nicht öffnen.

### Schritt 2: Daten an Edge Impulse senden

1. Im Terminal `edge-impulse-data-forwarder` starten.
2. Mit dem Edge-Impulse-Konto anmelden und das Projekt wählen.
3. Die CLI erkennt 3 Achsen bei etwa 100 Hz. Als Achsennamen `accX,accY,accZ` eingeben, als Gerätename zum Beispiel `esp32s3`.
4. Im Browser unter **Data acquisition** erscheint das Gerät. Sample length auf 10000 ms setzen, Label eintragen, **Start sampling** klicken und die Bewegung 10 Sekunden lang ausführen.
5. Pro Klasse etwa 12 Aufnahmen machen (rund 2 Minuten), dabei leicht variieren: schneller, langsamer, Board in der anderen Hand.
   - `ruhe`: Board liegt auf dem Tisch, auch mal schräg oder in der ruhigen Hand
   - `schuetteln`: kräftig hin und her
   - `kreisen`: Kreise in der Luft, etwa einmal pro Sekunde
   - `sonstiges`: aufheben, ablegen, drehen, langsam herumtragen
6. Unter **Dashboard > Danger zone** auf **Perform train / test split** klicken, damit rund 20 Prozent als Testdaten zurückgehalten werden.

### Schritt 3: Modell in Edge Impulse erstellen

1. **Create impulse**: Window size 2000 ms, Window increase 200 ms, Frequency 100 Hz. Processing block **Spectral Analysis**, Learning block **Classification** hinzufügen, **Save Impulse**.
2. **Spectral features**: Standardwerte übernehmen, **Save parameters**, dann **Generate features**. Im Feature explorer sollten die vier Klassen als getrennte Punktwolken erscheinen.
3. **Classifier**: Standardwerte lassen (30 Trainingszyklen), **Start training**. Ziel: über 90 Prozent Genauigkeit. Oben rechts auf **Quantized (int8)** umschalten und RAM, Flash und Rechenzeit ablesen.
4. **Model testing**: **Classify all** prüft das Modell mit den zurückgehaltenen Testdaten.
5. **Deployment**: **Arduino library** wählen, Optimierung **Quantized (int8)**, EON Compiler eingeschaltet lassen, **Build**. Eine Datei wie `ei-bewegung-esp32s3-arduino-1.0.1.zip` wird heruntergeladen.

### Schritt 4: Bibliothek in die Arduino IDE einbinden

1. **Sketch > Bibliothek einbinden > .ZIP-Bibliothek hinzufügen** und die heruntergeladene Datei wählen.
2. Der Name der Header-Datei steht unter **Datei > Beispiele > bewegung-esp32s3 Inferencing**. Er lautet `<Projektname>_inferencing.h`, also zum Beispiel `bewegung-esp32s3_inferencing.h`.
3. Den Erkennungs-Sketch anlegen und die erste `#include`-Zeile an deinen Projektnamen anpassen.

### Schritt 5: Erkennungs-Sketch

Der Sketch [02_bewegungserkennung](sketches/02_bewegungserkennung/02_bewegungserkennung.ino) sammelt jeweils ein Fenster von 2 Sekunden, lässt das Modell rechnen und gibt das Ergebnis aus. Ein Ergebnis gilt nur als erkannt, wenn die Konfidenz mindestens 80 Prozent beträgt.

Der erste Kompiliervorgang dauert mehrere Minuten, weil die Bibliothek viele Quelldateien enthält. Im seriellen Monitor (115200 Baud) erscheint danach alle gut 2 Sekunden eine Zeile wie:

```text
DSP 9 ms, Modell 1 ms | kreisen: 0.03  ruhe: 0.01  schuetteln: 0.95  sonstiges: 0.01
==> Erkannt: schuetteln
```

Die Zahlen sind ein Beispiel; deine Werte hängen vom Modell ab.

## Fehlersuche

| Problem | Ursache und Lösung |
| --- | --- |
| "MPU6050 nicht gefunden" | SDA und SCL vertauscht, falsche GPIOs oder Wackelkontakt. Mit einem I2C-Scanner-Sketch prüfen, ob 0x68 antwortet. |
| Neustart-Schleife, PSRAM 0 KB | PSRAM-Einstellung passt nicht zum Modul: R8 = OPI PSRAM, R2 = QSPI PSRAM. |
| Kein Text im seriellen Monitor | Bei der nativen USB-Buchse "USB CDC On Boot" auf Enabled stellen, oder die UART-Buchse nutzen. |
| Data Forwarder findet kein Gerät | Seriellen Monitor der Arduino IDE schließen. Mit `edge-impulse-data-forwarder --clean` neu anmelden. |
| Kompilierfehler "initializer clauses should be designated" | ESP32-Core zu neu für den Export. Im Boardverwalter ältere Version wählen (3.1.x, notfalls 2.0.17) oder das Modell neu exportieren. |
| Erkennung am Gerät schlechter als in Edge Impulse | Messbereich oder Abtastrate weichen vom Training ab, oder die Daten waren zu einheitlich. Mehr und vielfältigere Aufnahmen machen. |

## Nächste Schritte

1. **Auf einen Lüfter übertragen:** Sensor auf das Lüftergehäuse kleben, Klassen `aus`, `normal`, `unwucht` (kleines Klebeband-Stück auf ein Flügelblatt) aufnehmen. Bei Vibration die Frequenz auf 200 bis 400 Hz erhöhen und das Fenster auf 1000 ms verkürzen.
2. **Ergebnis an einen Raspberry Pi:** Nur bei einer Erkennung über dem Schwellwert per MQTT senden (Bibliothek PubSubClient, Topic zum Beispiel `werkstatt/esp32s3/bewegung`). Auf dem Pi Mosquitto und Node-RED oder Grafana zur Anzeige.
3. **Anomalieerkennung:** In Edge Impulse zusätzlich den Block "Anomaly Detection (K-means)" hinzufügen. Er meldet Zustände, die in keiner Trainingsklasse vorkamen.
4. **Audio oder Bild:** Mit dem XIAO ESP32S3 Sense ein Schlüsselwort-Modell ("an", "aus") trainieren. Ab hier lohnt der Blick auf ESP-DL und ESP-IDF.

Passende Tutorials zu allen Punkten stehen im [Lernpfad](../lernpfad/).

## Quellen

- [Arduino IDE 2.3.10 Ankündigung (Arduino Forum)](https://forum.arduino.cc/t/arduino-ide-2-3-10-is-now-available/1447778)
- [Arduino IDE Download](https://www.arduino.cc/en/software)
- [arduino-esp32 in der ESP Component Registry](https://components.espressif.com/components/espressif/arduino-esp32/versions/3.3.13/readme)
- [Edge Impulse: Arduino Library (Dokumentation)](https://docs.edgeimpulse.com/docs/run-inference/arduino-library)
- [Edge Impulse Forum: Kompilierfehler mit arduino-esp32 Core 3.x](https://forum.edgeimpulse.com/t/fix-for-compilation-error-when-using-arduino-esp32-core-v3-x/12220)

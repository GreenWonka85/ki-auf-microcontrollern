# Sketches zur ESP32-S3-Anleitung

> **Hinweis:** Diese Sketches wurden noch nicht auf echter Hardware getestet.

| Ordner | Zweck |
| --- | --- |
| [00_funktionstest](00_funktionstest/) | Prüft Chip, Flash und PSRAM nach der Einrichtung |
| [01_datenaufnahme_mpu6050](01_datenaufnahme_mpu6050/) | Liest den MPU6050 mit 100 Hz aus und liefert Daten für den Edge Impulse Data Forwarder |
| [02_bewegungserkennung](02_bewegungserkennung/) | Führt das in Edge Impulse trainierte Modell auf dem ESP32-S3 aus |

Jeder Sketch liegt in einem eigenen Ordner mit gleichem Namen, so wie es die Arduino IDE erwartet.

Für den XIAO ESP32S3 in den Sketches `SDA_PIN = 5` und `SCL_PIN = 6` setzen.

Sketch 2 benötigt die aus Edge Impulse exportierte Arduino-Bibliothek. Die erste `#include`-Zeile muss an den eigenen Projektnamen angepasst werden. Details in der [Anleitung](../README.md#schritt-4-bibliothek-in-die-arduino-ide-einbinden).

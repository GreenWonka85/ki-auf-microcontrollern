# KI auf Microcontrollern

Persönliche Sammlung von Tutorials und Anleitungen zum Lernen von KI auf Microcontrollern (TinyML), mit Schwerpunkt ESP32-S3, Arduino IDE und Edge Impulse.

Deutschsprachiges Lernmaterial zum Einstieg in TinyML: maschinelles Lernen direkt auf Microcontrollern wie dem ESP32-S3. Die Sammlung richtet sich an Einsteiger, Azubis und alle, die bereits mit Arduino oder ESP32 gearbeitet haben und nun eigene KI-Modelle auf kleiner Hardware ausführen möchten.

> **Hinweis:** Die Sketches in diesem Repository wurden noch nicht auf echter Hardware getestet. Sie sind sorgfältig erstellt, können aber Fehler enthalten. Rückmeldungen und Korrekturen über Issues oder Pull Requests sind willkommen.

## Inhalt

| Bereich | Beschreibung |
| --- | --- |
| [grundlagen/](grundlagen/) | Welche IDE und welcher Microcontroller eignen sich für den Einstieg? |
| [esp32-s3/](esp32-s3/) | Schritt-für-Schritt-Anleitung: Arduino IDE, ESP32-S3 mit PSRAM und Edge Impulse, mit Schnupperprojekt Bewegungserkennung (MPU6050) |
| [esp32-s3/sketches/](esp32-s3/sketches/) | Arduino-Sketches zur Anleitung als `.ino`-Dateien |
| [lernpfad/](lernpfad/) | Kuratierte Tutorial-Sammlung in neun Kapiteln, von den Grundlagen bis zur MQTT-Anbindung an den Raspberry Pi |

## Empfohlener Einstieg

1. [Grundlagen](grundlagen/) lesen und Board auswählen.
2. Der [ESP32-S3-Anleitung](esp32-s3/) folgen und das Schnupperprojekt umsetzen.
3. Mit dem [Lernpfad](lernpfad/) vertiefen: Kapitel 1 bis 4 vollständig, dann ein eigenes Projekt, danach Kapitel 8.

## Verwendeter Stack

- Arduino IDE 2 mit dem Boardpaket "esp32 by Espressif Systems"
- ESP32-S3 mit PSRAM (DevKitC-1 N16R8 oder N8R8, alternativ Seeed XIAO ESP32S3 Sense)
- Edge Impulse für Datenaufnahme, Training und Quantisierung
- MPU6050 als Beschleunigungssensor für das erste Projekt

## Erweiterung

Die Struktur ist nach Boards und Themen gegliedert. Weitere Boards (zum Beispiel STM32 oder Arduino Nano 33 BLE Sense) erhalten jeweils einen eigenen Ordner nach dem Muster von `esp32-s3/`. Themenübergreifende Inhalte gehören nach `grundlagen/` oder `lernpfad/`.

## Lizenz

- Texte und Anleitungen: [Creative Commons Namensnennung 4.0 International (CC BY 4.0)](https://creativecommons.org/licenses/by/4.0/deed.de)
- Quellcode (Sketches): [MIT-Lizenz](LICENSE)

Details siehe [LIZENZ.md](LIZENZ.md).

Stand: November 2026

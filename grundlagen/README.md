# Grundlagen: IDE und Board auswählen

Für den Einstieg empfehlen wir: **Arduino IDE 2 + ESP32-S3 mit PSRAM + Edge Impulse**. Edge Impulse übernimmt Training und Quantisierung im Browser und liefert das fertige Modell als Arduino-Bibliothek. Wer die Arduino IDE vom ESP32 kennt, braucht nur einen neuen Baustein.

## Welche IDE?

| IDE | Aufwand | Wann sinnvoll |
| --- | --- | --- |
| Arduino IDE 2 | gering | Einstieg, Edge-Impulse-Export direkt als .zip-Bibliothek einbindbar. **Empfohlen.** |
| PlatformIO in VS Code | mittel | Größere Projekte, Versionsverwaltung, mehrere Boards. Edge-Impulse-Bibliothek lässt sich in den Ordner lib/ kopieren. |
| ESP-IDF (Espressif) | hoch | Volle Kontrolle, ESP-DL für Bild und Audio, Produktentwicklung. Später interessant. |
| STM32CubeIDE + ST Edge AI | hoch | Nur bei STM32-Hardware. |

Die IDE ist bei TinyML zweitrangig: Trainiert wird immer in Edge Impulse oder am PC, die IDE kompiliert nur den exportierten C++-Code zusammen mit deinem Sketch.

## Welcher Microcontroller ist am einfachsten?

| Board | Einstieg | Begründung |
| --- | --- | --- |
| ESP32-S3-DevKitC-1 N16R8 oder N8R8 | sehr einfach | Gleiche Arduino-Welt wie der klassische ESP32, 8 MB PSRAM, Vektorbefehle für KI (ESP-NN). **Empfohlen für den Einstieg.** |
| Seeed XIAO ESP32S3 Sense | sehr einfach | Kamera und Mikrofon an Bord, 8 MB PSRAM, sehr klein. Ideal für den zweiten Schritt (Audio, Bild). |
| Arduino Nano 33 BLE Sense | einfach | Sensoren eingebaut, offizielle Edge-Impulse-Firmware, aber teurer und ohne WLAN. |
| ESP32 klassisch | eingeschränkt | Für Bewegungsdaten ausreichend, kein PSRAM bei vielen Boards, keine KI-Vektorbefehle. |
| STM32 (F4, H7, N6) | mittel bis aufwendig | Starke Werkzeuge, aber neue Toolchain. |

Beim Kauf auf die Bezeichnung achten: **N16R8** bedeutet 16 MB Flash und 8 MB PSRAM. Boards ohne "R" haben kein PSRAM.

## Weiter

- [Anleitung ESP32-S3](../esp32-s3/)
- [Lernpfad](../lernpfad/)

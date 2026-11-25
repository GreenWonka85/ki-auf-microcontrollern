# TinyML Lernpfad

Diese Sammlung führt in neun Kapiteln von den Grundlagen bis zur Anbindung an den Raspberry Pi. Wer die Kapitel der Reihe nach durcharbeitet, hat am Ende ein eigenes TinyML-Projekt auf dem ESP32-S3 laufen. Alle Links wurden am 24.11.2026 abgerufen und waren erreichbar.

**Zur Sprache:** Deutschsprachige Quellen stehen jeweils vorne. Zu Edge Impulse, ESP-DL, LiteRT und ST Edge AI gibt es praktisch nur englische Originaldokumentation; diese Einträge sind mit **EN** gekennzeichnet. Die Browser-Übersetzung macht sie gut lesbar. **DE (maschinell)** bedeutet, dass der Anbieter selbst eine automatische Übersetzung bereitstellt.

**Empfohlener Weg für Einsteiger und Azubis:** Kapitel 1 bis 4 vollständig, dann ein eigenes Projekt (zum Beispiel Lüfterüberwachung, siehe [ESP32-S3-Anleitung](../esp32-s3/)), danach Kapitel 8. Kapitel 5 bis 7 sind Vertiefung.

## Inhalt

1. [Grundlagen](#kapitel-1-grundlagen)
2. [Werkzeuge, Hardware und Sensoren einrichten](#kapitel-2-werkzeuge-hardware-und-sensoren-einrichten)
3. [Erste Projekte mit Edge Impulse](#kapitel-3-erste-projekte-mit-edge-impulse)
4. [Signalverarbeitung und Merkmale](#kapitel-4-signalverarbeitung-und-merkmale)
5. [TensorFlow Lite for Microcontrollers (LiteRT) selbst nutzen](#kapitel-5-tensorflow-lite-for-microcontrollers-litert-selbst-nutzen)
6. [Quantisierung und Optimierung](#kapitel-6-quantisierung-und-optimierung)
7. [Fortgeschrittene Themen](#kapitel-7-fortgeschrittene-themen)
8. [Anbindung an den Raspberry Pi per MQTT](#kapitel-8-anbindung-an-den-raspberry-pi-per-mqtt)
9. [Kurse und Bücher zur Vertiefung](#kapitel-9-kurse-und-bücher-zur-vertiefung)

## Kapitel 1: Grundlagen

Ziel: verstehen, was TinyML ist, wie ein neuronales Netz grundsätzlich arbeitet und warum Modelle für Microcontroller verkleinert werden müssen.

| Nr. | Titel | Sprache | Art | Beschreibung |
| --- | --- | --- | --- | --- |
| 1.1 | [Was ist TinyML? (DataCamp)](https://www.datacamp.com/de/blog/what-is-tinyml-tiny-machine-learning) | DE | Artikel | Kompakte Einführung: Definition, Vorteile, Anwendungen, typische Boards (u. a. ESP32-DevKitC, ESP-EYE). Guter erster Text. |
| 1.2 | [Was ist TinyML? (Computerwoche)](https://www.computerwoche.de/article/2814367/was-ist-tinyml.html) | DE | Artikel | Einordnung aus Praxissicht: Training in der Cloud, Ausführung auf dem Microcontroller, Werkzeuge TensorFlow Lite Micro und Edge Impulse. |
| 1.3 | [Neuronale Netze (Studyflix)](https://studyflix.de/informatik/neuronale-netze-4297) | DE | Video (ca. 5 Min.) und Text | Aufbau und Funktionsweise neuronaler Netze an einem einfachen Beispiel. Sehr gut für Azubis. |
| 1.4 | [Was sind neuronale Netze? (DataCamp)](https://www.datacamp.com/de/blog/what-are-neural-networks) | DE | Artikel | Netztypen, Training, Vor- und Nachteile, mit kleinem Keras-Beispiel. |
| 1.5 | [Neural Networks (KI-Campus)](https://ki-campus.org/node/209?locale=de) | Oberfläche DE, Videos EN | Videoreihe | Vierteilige, sehr anschauliche Videoreihe von 3Blue1Brown zu Netzen, Gradientenabstieg und Backpropagation. |
| 1.6 | [TinyML: AI for Microcontrollers (DesignSpark)](https://www.rs-online.com/designspark/tinyml-ai-for-microcontrollers-de) | DE | Fachartikel | Erklärt CNNs, 8-Bit-Quantisierung und Netzverkleinerung für Microcontroller. Brücke zu Kapitel 6. |
| 1.7 | [Edge AI lifecycle (Edge Impulse)](https://docs.edgeimpulse.com/docs/concepts/edge-ai-fundamentals/edge-ai-lifecycle) | EN | Text, Video, Quiz | Der komplette Projektablauf von der Datensammlung bis zur Wartung. |
| 1.8 | [Efficient AI / TinyML (Fraunhofer IIS)](https://www.iis.fraunhofer.de/de/ff/lv/dataanalytics/tinyml.html) | DE | Info-Seite | Industrielle Anwendungsfelder wie Condition Monitoring und Sprachanalyse. Zur Motivation, kein Tutorial. |

## Kapitel 2: Werkzeuge, Hardware und Sensoren einrichten

Ziel: Edge-Impulse-Konto anlegen, Board verbinden und Sensordaten sauber auslesen, bevor KI ins Spiel kommt.

| Nr. | Titel | Sprache | Art | Beschreibung |
| --- | --- | --- | --- | --- |
| 2.1 | [ESP32 mit Beschleunigungssensor: Tutorial für Anfänger (usro)](https://blog.usro.net/de/2025/04/esp32-mit-beschleunigungssensor-vollstandiges-tutorial-fur-anfanger/) | DE | Artikel | MPU6050 (alternativ ADXL345) per I2C an den ESP32 anschließen und in der Arduino IDE auslesen. |
| 2.2 | [Lektion 05: MPU6050 am ESP32 (SunFounder)](https://docs.sunfounder.com/projects/umsk/de/latest/03_esp32/esp32_lesson05_mpu6050.html) | DE | Anleitung | Schaltung und Sketch mit der Adafruit-MPU6050-Bibliothek: Beschleunigung, Gyroskop, Temperatur. |
| 2.3 | [ESP32 with INMP441 I2S Microphone (Random Nerd Tutorials)](https://randomnerdtutorials.com/esp32-inmp441-i2s-microphone-arduino/) | EN | Anleitung | INMP441 am ESP32-S3 DevKitC: Pegel messen, Wellenform im Serial Plotter, Klatschschalter. Vorbereitung für Sprachbefehle. |
| 2.4 | [Edge Impulse (Startseite, Konto anlegen)](https://edgeimpulse.com) | EN | Plattform | Kostenloses Entwicklerkonto für Edge Impulse Studio. |
| 2.5 | [Edge Impulse Dokumentation](https://docs.edgeimpulse.com/) | EN | Doku | Einstieg in Studio, CLI, unterstützte Hardware und Tutorials, mit Einführungsvideo. |
| 2.6 | [Edge Impulse: Espressif ESP32](https://docs.edgeimpulse.com/hardware/boards/espressif-esp32) | EN | Doku mit Video | ESP32 mit Edge Impulse verbinden: Firmware flashen, edge-impulse-daemon, Datenaufnahme direkt vom Board. |
| 2.7 | [Edge Impulse: Seeed XIAO ESP32S3 Sense](https://docs.edgeimpulse.com/hardware/boards/seeed-xiao-esp32s3-sense) | EN | Doku | Kurzbeschreibung des Einsteigerboards mit Kamera und Mikrofon, Export als Arduino-Bibliothek. |
| 2.8 | [TinyML-Themenseite (Seeed Studio Wiki)](https://wiki.seeedstudio.com/tinyml_topic/) | EN | Übersicht | Sammlung von Boards, Werkzeugen und Tutorials rund um XIAO ESP32S3 Sense und weitere Seeed-Boards. |

Hinweis: Eine geprüfte deutschsprachige Anleitung speziell für die Einrichtung des ESP32-S3 mit PSRAM in der Arduino IDE war bei der Recherche nicht zu finden. Wichtig ist dort vor allem, im Menü "Werkzeuge" die Option PSRAM auf "OPI PSRAM" zu stellen (bei Modulen mit 8 MB PSRAM). Die [ESP32-S3-Anleitung](../esp32-s3/) in diesem Repository beschreibt die Einrichtung vollständig.

## Kapitel 3: Erste Projekte mit Edge Impulse

Ziel: ein vollständiges Projekt von der Datenaufnahme bis zum laufenden Modell auf dem Board. Mit Bewegungsdaten beginnen, danach Audio.

| Nr. | Titel | Sprache | Art | Beschreibung |
| --- | --- | --- | --- | --- |
| 3.1 | [ESP32-S3-TinyML-Leitfaden (OpenELAB)](https://openelab.io/de/blogs/learn/esp32-s3-tinyml-image-audio-sensor-models) | DE | Artikel | Überblick, welche Modelle (Bild, Audio, Sensor) auf dem ESP32-S3 sinnvoll laufen, mit Edge Impulse und LiteRT Micro, Beispiele mit XIAO ESP32S3 Sense. |
| 3.2 | [Motion recognition with anomaly detection (Edge Impulse)](https://docs.edgeimpulse.com/tutorials/end-to-end/motion-recognition) | EN | Tutorial mit Video | **Das zentrale Einstiegsprojekt.** Bewegungen aus Beschleunigungsdaten klassifizieren: Spectral Analysis, neuronales Netz, Anomalieerkennung mit K-Means, Deployment. 1:1 übertragbar auf die Lüfterüberwachung. |
| 3.3 | [AI Workshop: How to Add AI to Almost Everything (Seeed)](https://wiki.seeedstudio.com/tinyml_workshop_course_new) | EN | Workshop | Einsteiger-Workshop auf dem XIAO ESP32S3 Sense mit SenseCraft AI: vom "AI Blink" bis zum eigenen Modell. Gut für eine Azubi-Einführung. |
| 3.4 | [XIAO ESP32S3 Sense Keyword Spotting (Seeed Wiki)](https://wiki.seeedstudio.com/xiao_esp32s3_keyword_spotting/) | EN | Anleitung | Sprachbefehl erkennen: Aufnahmen auf SD-Karte, Training in Edge Impulse (MFCC, CNN), Export als Arduino-Bibliothek, LED schaltet auf Zuruf. |
| 3.5 | [TinyML Made Easy: Keyword Spotting (Hackster, M. Rovai)](https://www.hackster.io/mjrobot/tinyml-made-easy-keyword-spotting-kws-5fa6e7) | EN | Anleitung | Ausführliche Variante mit den Klassen YES, NO, Noise und Unknown auf dem XIAO ESP32S3 Sense. Zeigt gut, warum "Unbekannt" und "Hintergrund" nötig sind. |
| 3.6 | [Train and deploy a TinyML audio classifier (Arm Learning Path)](https://learn.arm.com/learning-paths/embedded-and-microcontrollers/edge/software-edge-impulse/) | EN | Tutorial mit Screenshots | Sprachbefehle "on" und "off" in Edge Impulse trainieren und als Arduino-Bibliothek exportieren. Board ist ein Arduino Nano RP2040, der Ablauf gilt genauso für den ESP32-S3. |
| 3.7 | [KI-Zauberstab mit TensorFlow Lite und Arduino (Google Codelab)](https://codelabs.developers.google.com/magicwand?hl=de) | DE (maschinell) | Codelab | Gestenerkennung (Wing, Ring, Slope) mit Beschleunigungssensor auf dem Arduino Nano 33 BLE Sense. Gutes Gestenprojekt für das klassische Lernboard. |

## Kapitel 4: Signalverarbeitung und Merkmale

Ziel: verstehen, warum FFT und Spektrogramm aus Rohdaten gute Merkmale machen. Das entscheidet oft mehr über die Erkennungsqualität als das Modell.

| Nr. | Titel | Sprache | Art | Beschreibung |
| --- | --- | --- | --- | --- |
| 4.1 | [Was ist die Fast Fourier Transform (FFT)? (Fluke)](https://www.fluke.com/de-de/mehr-erfahren/blog/trasse/what-is-the-fast-fourier-transform-fft) | DE | Fachartikel | Zeitsignal gegen Frequenzspektrum, erklärt an Maschinenfehlern wie Unwucht und Fehlausrichtung. Ideal als Hintergrund für die Lüfterüberwachung. |
| 4.2 | [Eine Anleitung zur Vibrationsanalyse (Farnell)](https://de.farnell.com/technical-resources/articles/guide-to-vibration-analysis) | DE | Fachartikel | Messung mit Schwingungssensoren, Auswertung per Frequenzanalyse und KI zur Früherkennung von Verschleiß. |
| 4.3 | [Edge AI Anomaly Detection Part 2: Feature Extraction and Model Training (DigiKey, Shawn Hymel)](https://www.digikey.de/de/videos/d/digi-key-electronics/edge-ai-anomaly-detection-part-2-feature-extraction-and-model-training) | EN | Video | Merkmalsextraktion aus Sensordaten und Training zweier Modelle zur Anomalieerkennung. Passt zu Projekten wie Motorüberwachung und Temperatur-Anomalien. |
| 4.4 | [Intro to TensorFlow Lite Part 1: Wake Word Feature Extraction (DigiKey)](https://www.digikey.fi/fi/videos/d/digi-key-electronics/intro-to-tensorflow-lite-part-1-wake-word-feature-extraction-maker-io-tutorial-digi-key-electronics) | EN | Video | Wie aus Audio MFCC-Merkmale (Spektrogramm) für die Spracherkennung werden. |
| 4.5 | [Intro to TensorFlow Lite Part 2: Speech Recognition Model Training (DigiKey)](https://www.digikey.com/en/videos/d/digi-key-electronics/intrototensorflowlitepart2speechrecognitionmodeltrainingmakeriotutorialdigikeyelectronics) | EN | Video | Fortsetzung: ein CNN auf diesen Audiomerkmalen mit Keras trainieren. |

## Kapitel 5: TensorFlow Lite for Microcontrollers (LiteRT) selbst nutzen

Ziel: ein Modell ohne Edge Impulse selbst in Python trainieren, umwandeln und auf dem Microcontroller ausführen. Mehr Handarbeit, dafür volle Kontrolle.

| Nr. | Titel | Sprache | Art | Beschreibung |
| --- | --- | --- | --- | --- |
| 5.1 | [Arduino-Demo mit TensorFlow Lite und Bluetooth Web API (mikrocontroller.net)](https://www.mikrocontroller.net/news/arduino-demo-mit-tensorflow-lite-und-bluetooth-web-api) | DE | Kurzartikel | Vorstellung eines Google-Beispielprojekts zur Gestenerkennung mit TensorFlow Lite auf dem Arduino Nano BLE. Zeigt, was mit TFLite Micro möglich ist. |
| 5.2 | [Intro to TinyML Part 1: Training a Model for Arduino in TensorFlow (DigiKey)](https://www.digikey.com/en/maker/projects/intro-to-tinyml-part-1-training-a-model-for-arduino-in-tensorflow/8f1fc8c0b83d417ab521c48864d2a8ec) | EN | Artikel | Kleines Netz für eine Sinusfunktion in TensorFlow trainieren, nach TensorFlow Lite umwandeln und mit Netron ansehen. |
| 5.3 | [Intro to TinyML Part 1 (Video)](https://www.digikey.co.uk/en/videos/d/digi-key-electronics/intro-to-tinyml-part-1-training-a-neural-network-for-arduino-in-tensorflow) | EN | Video | Derselbe Inhalt als Video. |
| 5.4 | [Intro to TinyML Part 2: Deploying a TensorFlow Lite Model to Arduino (DigiKey)](https://www.digikey.at/de/videos/d/digi-key-electronics/intro-to-tinyml-part-2-deploying-a-tensorflow-lite-model-to-arduino) | EN (Seite DE) | Video | Das trainierte Modell auf den Microcontroller bringen und ausführen. |
| 5.5 | [LiteRT for Microcontrollers: Übersicht (Google)](https://developers.google.com/edge/litert/microcontrollers/overview) | EN | Doku | Offizielle Einführung, Speicherbedarf, unterstützte Boards (u. a. ESP32-DevKitC, ESP-EYE). |
| 5.6 | [Get started with microcontrollers (Google)](https://developers.google.com/edge/litert/microcontrollers/get_started) | EN | Tutorial | Das offizielle Hello-World-Beispiel, getestet unter anderem mit ESP32 und ESP-IDF. |
| 5.7 | [tflite-micro (GitHub)](https://github.com/tensorflow/tflite-micro) | EN | Quellcode | Bibliothek und Beispiele, mit Verweis auf die ESP32-Portierung von Espressif. |
| 5.8 | [KI-Spracherkennung mit TensorFlow Lite und SparkFun Edge (Google Codelab)](https://codelabs.developers.google.com/codelabs/sparkfun-tensorflow/?hl=de) | DE (maschinell) | Codelab | Ja/Nein-Spracherkennung auf dem SparkFun Edge mit eigenem Build. Älteres Board, aber der Ablauf ist lehrreich. |

## Kapitel 6: Quantisierung und Optimierung

Ziel: Modelle auf int8 verkleinern und den Speicherbedarf so weit senken, dass sie in RAM und Flash des Microcontrollers passen.

| Nr. | Titel | Sprache | Art | Beschreibung |
| --- | --- | --- | --- | --- |
| 6.1 | [Whitepaper: KI auf Mikrocontrollern (HdM Stuttgart)](https://ai.hdm-stuttgart.de/downloads/student-white-paper/Winter-2122/KI_auf_Mikrocontrollern.pdf) | DE | PDF | Studentische Arbeit: ein Ziffernerkennungsnetz durch 8-Bit-Quantisierung, kleinere Eingaben und Pruning so verkleinert, dass es sogar auf einen ATmega328p passt. Sehr anschaulich. |
| 6.2 | [Vom Modell zum Mikrocontroller (Lars Gregori, Speaker Deck)](https://speakerdeck.com/choas23/vom-modell-zum-mikrocontroller-intelligenz-in-kleinen-dimensionen) | DE | Vortragsfolien | 26 Folien von 11/2025 zum Weg vom trainierten Modell zum Microcontroller, Beispiel Raspberry Pi Pico mit TensorFlow Lite Micro. |
| 6.3 | [Post-training quantization (Google)](https://developers.google.com/edge/litert/models/post_training_quantization) | EN | Doku | Überblick der Quantisierungsarten: Dynamic Range, Full Integer, Float16. Für Microcontroller ist Full Integer (int8) der richtige Weg. |
| 6.4 | [Post-training integer quantization (Google)](https://developers.google.com/edge/litert/conversion/tensorflow/quantization/post_training_integer_quant) | EN | Tutorial mit Code | Schritt für Schritt ein Keras-Modell vollständig auf int8 quantisieren. |
| 6.5 | [LiteRT 8-bit quantization specification (Google)](https://developers.google.com/edge/litert/quantization/quantization_spec) | EN | Referenz | Die genaue Rechenvorschrift der int8-Quantisierung. Nur für Interessierte. |

In Edge Impulse läuft die Quantisierung automatisch; dort zeigt die Seite "Deployment" RAM, Flash und Rechenzeit für int8 und float32 nebeneinander.

## Kapitel 7: Fortgeschrittene Themen

Ziel: Bildverarbeitung auf dem ESP32-S3, optimierte Herstellerbibliotheken und der Blick auf STM32. Hier gibt es fast nur englische Quellen.

### ESP32-S3 und Bildverarbeitung

| Nr. | Titel | Sprache | Art | Beschreibung |
| --- | --- | --- | --- | --- |
| 7.1 | [TinyML Made Easy (E-Book, M. Rovai)](https://mjrovai.github.io/TinyML_Made_Easy_XIAO_ESP32S3_ebook/TinyML-Made-Easy.pdf) | EN | Kostenloses E-Book (PDF) | Komplettes Praxisbuch für den XIAO ESP32S3 Sense: Bildklassifikation, Objekterkennung (FOMO), Keyword Spotting, Bewegung und Anomalien. Sehr empfehlenswert. |
| 7.2 | [XIAO: Big Power, Small Board, Kapitel 4.1 (E-Book)](https://mjrovai.github.io/XIAO_Big_Power_Small_Board-ebook/chapter_4-1.html) | EN | Online-Buch | Einführung in TinyML und Edge Impulse Studio mit XIAO-Boards. Eignet sich gut für Azubis. |
| 7.3 | [Labs: XIAO ESP32S3 (Machine Learning Systems, Harvard)](https://mlsysbook.ai/contents/labs/seeed/xiao_esp32s3/xiao_esp32s3.html) | EN | Übungen | Vier Labore: Bildklassifikation, Objekterkennung, Keyword Spotting, Bewegungsklassifikation mit Anomalieerkennung. |
| 7.4 | [Labs: Übersicht (Machine Learning Systems)](https://mlsysbook.ai/contents/labs/overview.html) | EN | Übersicht | Alle Labore für XIAO ESP32S3, Nicla Vision und Raspberry Pi im Vergleich. |
| 7.5 | [ESP-DL: Getting Started (Espressif)](https://docs.espressif.com/projects/esp-dl/en/latest/getting_started/readme.html) | EN | Doku | Einstieg in die optimierte KI-Bibliothek für ESP32-S3 und ESP32-P4: ESP-IDF ab v5.3, Quantisierung mit esp-ppq, Beispiele bauen. Klassischer ESP32 nur eingeschränkt. |
| 7.6 | [ESP-DL (GitHub)](https://github.com/espressif/esp-dl) | EN | Quellcode | Bibliothek, Model Zoo und Beispiele, unter anderem YOLO11-Objekterkennung und Texterkennung (PP-OCR). |

### STM32 und ST Edge AI

| Nr. | Titel | Sprache | Art | Beschreibung |
| --- | --- | --- | --- | --- |
| 7.7 | [ST Edge AI Documentation](https://dev.st.com/edge-ai-docs/general/latest/en/index.html) | EN | Doku | Einstiegsseite zu allen ST-Werkzeugen: STM32Cube AI Studio, ST Edge AI Core, NanoEdge AI Studio, Model Zoo, Developer Cloud. |
| 7.8 | [Getting started with ST Edge AI Developer Cloud (ST Wiki)](https://wiki.st.com/stm32mcu/wiki/AI:Getting_started_with_ST_Edge_AI_Developer_Cloud) | EN | Anleitung | Modell im Browser hochladen, quantisieren, auf echten STM32-Boards benchmarken und Code erzeugen. |
| 7.9 | [ST Edge AI Developer Cloud](https://stm32ai.st.com/st-edge-ai-dc/) | EN | Plattform | Kostenlose Online-Plattform (Login mit MyST-Konto), auch für STM32N6 mit NPU. |
| 7.10 | [Getting Started with STM32Cube AI Studio (ST)](https://dev.st.com/edge-ai-docs/general/latest/en/docs/tutorials/stm32cube-ai-studio-getting-started.html) | EN | Tutorial | Ein int8-Bildmodell auf dem STM32N6570-DK mit NPU validieren und als Projekt exportieren. |
| 7.11 | [How to use Teachable Machine for image classification on STM32 (ST Wiki)](https://wiki.st.com/stm32mcu/wiki/AI:How_to_use_Teachable_Machine_to_create_an_image_classification_application_on_STM32) | EN | Anleitung | Bildklassifikator im Browser mit Google Teachable Machine trainieren und auf STM32 bringen. |
| 7.12 | [STM32 Model Zoo (GitHub)](https://github.com/STMicroelectronics/stm32ai-modelzoo) | EN | Modelle | Vortrainierte, für STM32 optimierte Modelle für Bild, Audio, Anomalien und Bewegungserkennung. |

## Kapitel 8: Anbindung an den Raspberry Pi per MQTT

Ziel: Der Microcontroller erkennt lokal und meldet nur das Ergebnis (zum Beispiel "Unwucht, Konfidenz 0,93") per MQTT an den Pi. Der Pi speichert, visualisiert und benachrichtigt.

| Nr. | Titel | Sprache | Art | Beschreibung |
| --- | --- | --- | --- | --- |
| 8.1 | [MQTT am Raspberry Pi: Mosquitto einrichten (raspberry.tips)](https://raspberry.tips/smart-home/mqtt-raspberry-pi) | DE | Anleitung | Mosquitto-Broker auf dem Pi installieren, Benutzer und Passwort anlegen, Beispiel mit einem Sensor als Publisher. Stand Oktober 2026. |
| 8.2 | [Video 46: IoT-Kommunikation mit MQTT (SunFounder ESP32)](https://docs.sunfounder.com/projects/esp32-starter-kit/de/latest/arduino_video_course/video_46_mqtt.html) | DE | Video und Text | ESP32 sendet Messwerte per MQTT und empfängt Befehle, programmiert in der Arduino IDE. |
| 8.3 | [ESP32 MQTT Publish Subscribe with Arduino IDE (Random Nerd Tutorials)](https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/) | EN | Anleitung | Genau diese Architektur: ESP32 mit PubSubClient, Mosquitto auf dem Raspberry Pi, Anzeige im Node-RED-Dashboard. Älter (2020), funktioniert aber weiterhin. |

Umsetzung im Edge-Impulse-Sketch: In der Schleife, in der das Beispiel das Ergebnis im seriellen Monitor ausgibt, statt `Serial.print` eine MQTT-Nachricht mit Klasse und Konfidenz senden. Nur senden, wenn die Konfidenz über dem Schwellwert liegt oder sich die Klasse ändert.

## Kapitel 9: Kurse und Bücher zur Vertiefung

Strukturierte Kurse mit Übungen, sinnvoll parallel zu Kapitel 3 bis 7. Einen deutschsprachigen TinyML-Kurs gibt es derzeit nicht; die Coursera-Kurse haben aber deutsche Untertitel.

| Nr. | Titel | Sprache | Art | Beschreibung |
| --- | --- | --- | --- | --- |
| 9.1 | [Einführung in eingebettetes maschinelles Lernen (Coursera, Edge Impulse)](https://www.coursera.org/de-DE/learn/introduction-to-embedded-machine-learning) | EN, Untertitel DE | Online-Kurs | **Bester Einstiegskurs.** Drei Module von Shawn Hymel: ML-Grundlagen, neuronale Netze, Audio und Keyword Spotting mit Edge Impulse. Kostenlos ohne Zertifikat. |
| 9.2 | [Computer Vision mit eingebettetem maschinellem Lernen (Coursera)](https://www.coursera.org/de-DE/learn/computer-vision-with-embedded-machine-learning) | EN, Oberfläche DE | Online-Kurs | Fortsetzung für Bilder: Bildklassifikation, CNNs, Objekterkennung auf Microcontrollern. |
| 9.3 | [Praktische Einführung in Deep Learning für Computer Vision (openHPI)](https://open.hpi.de/courses/neuralnets2020) | DE | Online-Kurs | Kostenloser deutscher Kurs zu neuronalen Netzen mit TensorFlow und Keras. Kein Microcontroller-Bezug, aber sehr gute Grundlage für Kapitel 5. Python-Vorkenntnisse nötig. |
| 9.4 | [Fundamentals of TinyML (HarvardX)](https://harvardonline.harvard.edu/course/fundamentals-tinyml) | EN | Online-Kurs | Erster Teil des Harvard-Zertifikatsprogramms, 5 Wochen mit 2 bis 4 Stunden pro Woche. Inhalte frei, Zertifikat kostenpflichtig. |
| 9.5 | [TinyML-Kurse auf edX](https://www.edx.org/learn/tinyml) | EN | Kursübersicht | Alle Harvard-Kurse: Fundamentals, Applications, Deploying TinyML. |
| 9.6 | [Freie TinyML-Kurse und Lehrmaterial (TinyMLedu, Harvard)](https://tinyml.seas.harvard.edu/courses) | EN | Linksammlung | Kurse, Folien und Workshops verschiedener Hochschulen, frei nutzbar, auch für die Ausbildung. |
| 9.7 | [TinyML (Pete Warden, Daniel Situnayake, O'Reilly)](https://www.oreilly.com/library/view/tinyml/9781492052036/) | EN | Buch | Das Standardwerk (2019): TensorFlow Lite for Microcontrollers mit Projekten wie Wake Word, Personenerkennung und Magic Wand. Teilweise veraltete Werkzeuge, Grundlagen weiterhin gut. |
| 9.8 | [Elektor: Edge Impulse Guest Edition](https://www.elektormagazine.com/elektor-edge-impulse) | EN | Magazinartikel, Webinare | Sammlung von Praxisartikeln, unter anderem ein ESP32-Energiezähler mit Edge-Impulse-Modell. Teilweise kostenpflichtig. |

## Nicht aufgenommen

Folgende Quellen ließen sich bei der Recherche nicht zuverlässig prüfen und wurden deshalb weggelassen: der heise-Artikel "KI-Überblick 3: Was sind neuronale Netze" (Abruf gesperrt), die AZ-Delivery-Reihe "MQTT auf dem Raspberry Pi und mit MicroPython auf der ESP-Familie" (Abruf gesperrt) und das Arduino-Tutorial "Edge Impulse with the Nano 33 BLE Sense" (Inhalt nicht lesbar). Alle drei sind vermutlich lesenswert und lassen sich im Browser direkt aufrufen.

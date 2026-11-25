// Sketch 2: Bewegungserkennung mit Edge Impulse auf dem ESP32-S3
// Voraussetzung: die aus Edge Impulse exportierte Arduino-Bibliothek ist installiert.
// Hinweis: noch nicht auf echter Hardware getestet.
#include <bewegung-esp32s3_inferencing.h> // an deinen Projektnamen anpassen
#include <Wire.h>

const int SDA_PIN = 8;          // XIAO ESP32S3: 5
const int SCL_PIN = 9;          // XIAO ESP32S3: 6
const uint8_t MPU_ADDR = 0x68;
const float LSB_PER_G = 8192.0f; // muss zur Datenaufnahme passen (+-4 g)
const float G_MS2 = 9.80665f;
const float CONFIDENCE_MIN = 0.80f;

#if EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME != 3
#error "Das Modell erwartet nicht 3 Achsen. Impulse in Edge Impulse pruefen."
#endif

static float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];

void mpuWrite(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

bool mpuInit() {
  Wire.beginTransmission(MPU_ADDR);
  if (Wire.endTransmission() != 0) return false;
  mpuWrite(0x6B, 0x01);
  delay(100);
  mpuWrite(0x1A, 0x03);
  mpuWrite(0x1C, 0x08);
  return true;
}

bool mpuReadAccel(float &ax, float &ay, float &az) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom(MPU_ADDR, (uint8_t)6) != 6) return false;
  uint8_t b[6];
  for (int i = 0; i < 6; i++) b[i] = Wire.read();
  ax = (int16_t)((b[0] << 8) | b[1]) / LSB_PER_G * G_MS2;
  ay = (int16_t)((b[2] << 8) | b[3]) / LSB_PER_G * G_MS2;
  az = (int16_t)((b[4] << 8) | b[5]) / LSB_PER_G * G_MS2;
  return true;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(SDA_PIN, SCL_PIN, 400000);
  while (!mpuInit()) {
    Serial.println("MPU6050 nicht gefunden, Verdrahtung pruefen");
    delay(1000);
  }
  Serial.printf("Modell: %d Klassen, Fenster %d Werte, Intervall %.1f ms\n",
                EI_CLASSIFIER_LABEL_COUNT, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE,
                (float)EI_CLASSIFIER_INTERVAL_MS);
}

void loop() {
  // 1. Ein Fenster Sensordaten im gleichen Takt wie beim Training sammeln
  const uint32_t intervalUs = (uint32_t)(EI_CLASSIFIER_INTERVAL_MS * 1000.0f);
  uint32_t next = micros();
  for (size_t i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; i += 3) {
    while ((int32_t)(micros() - next) < 0) { }
    next += intervalUs;
    float ax = 0, ay = 0, az = 0;
    mpuReadAccel(ax, ay, az);
    features[i + 0] = ax;
    features[i + 1] = ay;
    features[i + 2] = az;
  }

  // 2. Modell ausfuehren
  signal_t signal;
  if (numpy::signal_from_buffer(features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal) != 0) {
    Serial.println("Fehler beim Erzeugen des Signals");
    return;
  }
  ei_impulse_result_t result = { 0 };
  EI_IMPULSE_ERROR err = run_classifier(&signal, &result, false);
  if (err != EI_IMPULSE_OK) {
    Serial.printf("run_classifier Fehler: %d\n", err);
    return;
  }

  // 3. Ergebnis ausgeben
  Serial.printf("DSP %d ms, Modell %d ms | ", result.timing.dsp, result.timing.classification);
  size_t best = 0;
  for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
    Serial.printf("%s: %.2f  ", result.classification[ix].label, result.classification[ix].value);
    if (result.classification[ix].value > result.classification[best].value) best = ix;
  }
  Serial.println();

  if (result.classification[best].value >= CONFIDENCE_MIN) {
    Serial.printf("==> Erkannt: %s\n", result.classification[best].label);
  } else {
    Serial.println("==> unsicher");
  }
}

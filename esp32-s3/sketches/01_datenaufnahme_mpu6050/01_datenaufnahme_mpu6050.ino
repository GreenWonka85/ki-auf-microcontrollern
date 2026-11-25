// Sketch 1: MPU6050-Daten fuer den Edge Impulse Data Forwarder
// Gibt 100 Mal pro Sekunde die drei Beschleunigungsachsen in m/s^2 aus, kommagetrennt.
// Hinweis: noch nicht auf echter Hardware getestet.
#include <Wire.h>

const int SDA_PIN = 8;          // XIAO ESP32S3: 5
const int SCL_PIN = 9;          // XIAO ESP32S3: 6
const uint8_t MPU_ADDR = 0x68;
const float LSB_PER_G = 8192.0f; // Messbereich +-4 g
const float G_MS2 = 9.80665f;
const uint32_t FREQ_HZ = 100;
const uint32_t INTERVAL_US = 1000000UL / FREQ_HZ;

void mpuWrite(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

bool mpuInit() {
  Wire.beginTransmission(MPU_ADDR);
  if (Wire.endTransmission() != 0) return false; // Sensor antwortet nicht
  mpuWrite(0x6B, 0x01); // aufwecken, Takt vom Gyro-PLL
  delay(100);
  mpuWrite(0x1A, 0x03); // digitaler Tiefpass ca. 44 Hz
  mpuWrite(0x1C, 0x08); // Beschleunigung +-4 g
  return true;
}

bool mpuReadAccel(float &ax, float &ay, float &az) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // ACCEL_XOUT_H
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom(MPU_ADDR, (uint8_t)6) != 6) return false;
  uint8_t b[6];
  for (int i = 0; i < 6; i++) b[i] = Wire.read();
  int16_t x = (int16_t)((b[0] << 8) | b[1]);
  int16_t y = (int16_t)((b[2] << 8) | b[3]);
  int16_t z = (int16_t)((b[4] << 8) | b[5]);
  ax = x / LSB_PER_G * G_MS2;
  ay = y / LSB_PER_G * G_MS2;
  az = z / LSB_PER_G * G_MS2;
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
}

void loop() {
  static uint32_t next = micros();
  while ((int32_t)(micros() - next) < 0) { }
  next += INTERVAL_US;

  float ax, ay, az;
  if (mpuReadAccel(ax, ay, az)) {
    Serial.printf("%.3f,%.3f,%.3f\n", ax, ay, az);
  }
}

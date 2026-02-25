#include <Wire.h>

#define L3G_ADDR 0x68   // change to 0x69 if SDO = 3.3V

// L3G4200D registers
#define CTRL_REG1 0x20
#define CTRL_REG4 0x23
#define OUT_X_L   0x28

void writeReg(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(L3G_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

void readRegs(uint8_t reg, uint8_t *buf, uint8_t len) {
  Wire.beginTransmission(L3G_ADDR);
  Wire.write(reg | 0x80);   // auto-increment
  Wire.endTransmission(false);
  Wire.requestFrom(L3G_ADDR, len);

  for (int i = 0; i < len; i++) {
    buf[i] = Wire.read();
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  // Power on, enable X Y Z, 100 Hz
  writeReg(CTRL_REG1, 0x0F);

  // ±2000 dps full scale
  writeReg(CTRL_REG4, 0x30);

  Serial.println("L3G4200D initialized");

  pinMode(2, OUTPUT);
}

void loop() {
  uint8_t data[6];
  readRegs(OUT_X_L, data, 6);

  int16_t gx = (int16_t)(data[1] << 8 | data[0]);
  int16_t gy = (int16_t)(data[3] << 8 | data[2]);
  int16_t gz = (int16_t)(data[5] << 8 | data[4]);

  Serial.print("GX: "); Serial.print(gx);
  Serial.print("  GY: "); Serial.print(gy);
  Serial.print("  GZ: "); Serial.println(gz);

  if (abs(gx) < 1000) {
    digitalWrite(2, HIGH);
  }
  else {
    digitalWrite(2, LOW);
  }

  delay(100);
}

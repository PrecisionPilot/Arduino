#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Most common LCD address is 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Wire.begin(21, 22);   // SDA, SCL

  lcd.init();           // initialize
  lcd.backlight();      // turn on backlight

  lcd.setCursor(0, 0);
  lcd.print("Wsgood UGAHacks");

  lcd.setCursor(0, 1);
  lcd.print("By: ESP32 + LCD");
}

void loop() {
}

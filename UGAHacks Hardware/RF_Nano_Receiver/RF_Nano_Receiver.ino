#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------- RF24 SETTINGS ----------
RF24 radio(10, 9);                 // CE, CSN (change if your RF Nano differs)
const byte address[6] = "S3A9Q";    // MUST match transmitter

// ---------- LCD SETTINGS ----------
LiquidCrystal_I2C lcd(0x27, 16, 2); // change 0x27 -> 0x3F if needed

struct Payload32 {
  char top[16];
  char bottom[16];
};

void lcdShow(const Payload32 &p) {
  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++) lcd.print(p.top[i]);
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) lcd.print(p.bottom[i]);
}

// Interpret LED command if top line begins with '1' or '0' (after skipping spaces)
void maybeSetLedFromTop(const Payload32 &p) {
  int i = 0;
  while (i < 16 && p.top[i] == ' ') i++;
  if (i < 16) {
    if (p.top[i] == '1') digitalWrite(LED_BUILTIN, HIGH);
    if (p.top[i] == '0') digitalWrite(LED_BUILTIN, LOW);
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  // LCD init
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RX Booting...");

  // Radio init
  if (!radio.begin()) {
    Serial.println("radio.begin() failed");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RF begin FAIL");
    while (1) {}
  }

  // Same reliable settings as TX
  radio.setChannel(120);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setCRCLength(RF24_CRC_16);
  radio.setAutoAck(true);
  radio.setRetries(5, 15);

  radio.openReadingPipe(0, address);
  radio.startListening();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RX Ready");
  lcd.setCursor(0,1);
  lcd.print("Waiting...");
  Serial.println("RX ready");
}

void loop() {
  if (radio.available()) {
    Payload32 p;
    radio.read(&p, sizeof(p));

    // Update LCD
    lcd.clear();
    lcdShow(p);

    // Optional: LED control via '1'/'0'
    maybeSetLedFromTop(p);

    // Debug print
    Serial.print("Top: ");
    for (int i = 0; i < 16; i++) Serial.print(p.top[i]);
    Serial.print(" | Bottom: ");
    for (int i = 0; i < 16; i++) Serial.print(p.bottom[i]);
    Serial.println();
  }
}

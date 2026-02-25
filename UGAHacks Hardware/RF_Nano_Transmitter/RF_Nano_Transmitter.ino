#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------- RF24 SETTINGS ----------
RF24 radio(10, 9);                 // CE, CSN (change if your RF Nano differs)
const byte address[6] = "S3A9Q";    // 5 bytes unique address (CHANGE if you want)

// ---------- LCD SETTINGS ----------
LiquidCrystal_I2C lcd(0x27, 16, 2); // change 0x27 -> 0x3F if needed

// Payload: exactly 32 bytes = 16 chars top + 16 chars bottom
struct Payload32 {
  char top[16];
  char bottom[16];
};

String inputLine;

// --- helper: copy/pad/truncate a String into fixed 16-char buffer ---
void fill16(char out[16], const String &s) {
  for (int i = 0; i < 16; i++) out[i] = ' ';
  int n = s.length();
  if (n > 16) n = 16;
  for (int i = 0; i < n; i++) out[i] = s[i];
}

// --- helper: show on LCD ---
void lcdShow(const Payload32 &p) {
  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++) lcd.print(p.top[i]);
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) lcd.print(p.bottom[i]);
}

// --- parse "top\\lbottom" (backslash + l) ---
Payload32 parseMessage(const String &raw) {
  Payload32 p;
  int idx = raw.indexOf("\\l");  // literal sequence \l

  String top = (idx >= 0) ? raw.substring(0, idx) : raw;
  String bottom = (idx >= 0) ? raw.substring(idx + 2) : "";

  top.trim();
  bottom.trim();

  fill16(p.top, top);
  fill16(p.bottom, bottom);
  return p;
}

void setup() {
  Serial.begin(115200);

  // LCD init
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TX Ready");
  lcd.setCursor(0,1);
  lcd.print("Type msg...");

  // Radio init
  if (!radio.begin()) {
    Serial.println("radio.begin() failed");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RF begin FAIL");
    while (1) {}
  }

  // More reliable settings for noisy environments
  radio.setChannel(120);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setCRCLength(RF24_CRC_16);
  radio.setAutoAck(true);
  radio.setRetries(5, 15); // delay, count

  radio.openWritingPipe(address);
  radio.stopListening();

  Serial.println("TX ready. Type a line and press enter.");
  Serial.println(R"(Format: top\lbottom  (example: Hello\lWorld))");
  Serial.println("Tip: send just '1' or '0' to control receiver LED.");
}

void loop() {
  // Read a full line from Serial (non-blocking-ish)
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\r') continue;
    if (c == '\n') {
      inputLine.trim();
      if (inputLine.length() > 0) {
        Payload32 p = parseMessage(inputLine);

        // show locally on TX LCD
        lcd.clear();
        lcdShow(p);

        // send with a few retries
        bool ok = false;
        for (int i = 0; i < 5 && !ok; i++) {
          ok = radio.write(&p, sizeof(p));
          delay(20);
        }

        Serial.print("Sent: ");
        Serial.println(ok ? "OK" : "FAILED");
      }
      inputLine = "";
    } else {
      inputLine += c;
    }
  }
}

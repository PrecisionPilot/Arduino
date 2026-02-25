#include <HardwareSerial.h>
#include <Arduino.h>

HardwareSerial Modem(2);  // UART2

// Adjust these if you want different pins
static const int MODEM_RX = 16;  // ESP32 RX2
static const int MODEM_TX = 17;  // ESP32 TX2
static const int BUTTON = 23;
static const int BUZZER = 5;
static const int LED = 2;

int groundSpeed = 255;

#define MOTORL1 18
#define MOTORL2 19
#define MOTORR1 21
#define MOTORR2 22

String readLine(uint32_t timeoutMs = 1000) {
  uint32_t start = millis();
  String line;
  while (millis() - start < timeoutMs) {
    while (Modem.available()) {
      char c = Modem.read();
      if (c == '\r') continue;
      if (c == '\n') {
        if (line.length() > 0) return line;
      } else {
        line += c;
      }
    }
    delay(1);
  }
  return line; // may be empty
}

void sendAT(const String& cmd) {
  Serial.println(">> " + cmd);
  Modem.print(cmd);
  Modem.print("\r\n");
}

bool waitFor(const String& token, uint32_t timeoutMs = 2000) {
  uint32_t start = millis();
  while (millis() - start < timeoutMs) {
    String line = readLine(timeoutMs);
    if (line.length()) {
      Serial.println("<< " + line);
      if (line.indexOf(token) != -1) return true;
      if (line.indexOf("ERROR") != -1) return false;
    }
  }
  return false;
}

void beep(uint32_t timeMs = 500) {
  ledcWrite(BUZZER, 200);
  delay(timeMs);
  ledcWrite(BUZZER, 0);
}

void setupSMS() {
  sendAT("AT");
  waitFor("OK", 1000);

  sendAT("ATE0");
  waitFor("OK", 1000);

  sendAT("AT+CPIN?");
  waitFor("READY", 2000);

  sendAT("AT+CMGF=1");          // text mode
  waitFor("OK", 1000);

  sendAT("AT+CSCS=\"GSM\"");    // charset
  waitFor("OK", 1000);

  sendAT("AT+CPMS=\"SM\",\"SM\",\"SM\""); // storage
  waitFor("OK", 2000);

  sendAT("AT+CNMI=2,1,0,0,0");  // new SMS indications
  waitFor("OK", 1000);

  Serial.println("SMS setup done.");
}

void sendSMS(const String& number, const String& msg) {
  // Start CMGS
  beep(500);
  Modem.print("AT+CMGS=\"");
  Modem.print(number);
  Modem.print("\"\r\n");

  // Wait for prompt ">"
  if (!waitFor(">", 5000)) {
    Serial.println("No > prompt for CMGS");
    return;
  }

  // Send message + Ctrl+Z
  Modem.print(msg);
  Modem.write(0x1A);  // Ctrl+Z

  // Wait for confirmation
  waitFor("+CMGS", 10000);
  waitFor("OK", 10000);
  beep(1000);
}

String receiveSMS(uint32_t timeoutMs = 3000) {
  uint32_t start = millis();
  bool gotHeader = false;

  while (millis() - start < timeoutMs) {
    String line = readLine(500);
    if (!line.length()) continue;

    Serial.println("<< " + line);

    // Skip header
    if (line.startsWith("+CMGR:")) {
      gotHeader = true;
      continue;
    }

    // First non-header line after +CMGR is the message body
    if (gotHeader && line != "OK") {
      return line;
    }
  }
  return "";
}


void setup() {
  Serial.begin(115200);
  Modem.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLDOWN);
  pinMode(BUZZER, OUTPUT);
  ledcAttach(BUZZER, 400, 8);
  pinMode(MOTORL1, OUTPUT);
  pinMode(MOTORL2, OUTPUT);
  pinMode(MOTORR1, OUTPUT);
  pinMode(MOTORR2, OUTPUT);
  delay(200);


  setupSMS();

  // Test send (replace with your number)
}

bool isActive = false;

void loop() {
  if (digitalRead(BUTTON) && !isActive) {
    sendSMS("+12266987985", "It's better to come in the sink than sink in the come");
    isActive = true;
  }
  if (!digitalRead(BUTTON) && isActive) {
    isActive = false;
  }

  // Watch for new message notifications: +CMTI: "SM",3
  if (Modem.available()) {
    String line = readLine(2000);
    if (line.length()) {
      Serial.println("<< " + line);

      if (line.startsWith("+CMTI:")) {
        // beep(100);
        // delay(100);
        // beep(100);
        // delay(100);
        // beep(100);
        // parse index after comma
        int comma = line.lastIndexOf(',');
        if (comma != -1) {
          int idx = line.substring(comma + 1).toInt();
          Serial.printf("New SMS index: %d\n", idx);

          // Read it
          sendAT("AT+CMGR=" + String(idx));
          String sms = receiveSMS();
          sms = sms.substring(1, sms.length() - 1);

          Serial.println("SMS BODY: [" + sms + "]");

          // Normalize

          sms.trim();
          sms.toUpperCase();

          if (sms == "ON") {
            digitalWrite(LED, HIGH);
          } else if (sms == "OFF") {
            digitalWrite(LED, LOW);
          }
          else if(sms == "S")//Standby
          {
            analogWrite(MOTORL1, 0);
            analogWrite(MOTORL2, 0);
            analogWrite(MOTORR1, 0);
            analogWrite(MOTORR2, 0);
          }
          else if(sms == "F")//Forward
          {
            analogWrite(MOTORL1, groundSpeed);
            analogWrite(MOTORL2, 0);
            analogWrite(MOTORR1, groundSpeed);
            analogWrite(MOTORR2, 0);

            delay(2000);

            analogWrite(MOTORL1, 0);
            analogWrite(MOTORR1, 0);
          }
          else if(sms == "B")//Backwards
          {
            analogWrite(MOTORL1, 0);
            analogWrite(MOTORL2, groundSpeed);
            analogWrite(MOTORR1, 0);
            analogWrite(MOTORR2, groundSpeed);

            delay(2000);

            analogWrite(MOTORL2, 0);
            analogWrite(MOTORR2, 0);
          }
          else {
            sendSMS("+12266987985", "Unknown cmd. Use ON/OFF");
          }

          // Optional: delete after reading
          sendAT("AT+CMGD=" + String(idx));
          waitFor("OK", 2000);
        }
      }
    }
  }
}

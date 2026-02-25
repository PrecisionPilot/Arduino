// B = ones digit (least significant)
#define B0 PC10
#define B1 PC11
#define B2 PC12
#define B3 PC0

// A = tens digit (most significant)
#define A0 PA10
#define A1 PB6
#define A2 PB8
#define A3 PB9

#define SERVO_PIN PB0

#define RED PB4
#define GREEN PB10
#define BLUE PB3

#define DISPLAY_DELAY_COUNT 10

// --------------------------------------------
// Helper: displayNumber(value)
// Splits number 0-99 into tens + ones,
// Converts each to binary and outputs
// --------------------------------------------
void displayNumber(int value) {
  // Turn off display
  if (value == -1) {
    digitalWrite(B0, LOW);
    digitalWrite(B1, HIGH);
    digitalWrite(B2, LOW);
    digitalWrite(B3, HIGH);
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);
    digitalWrite(A3, HIGH);
    return;
  }
  value = min(value, 99);
  value = max(value, 0);

  int ones = value % 10;      // 0–9   → B nibble
  int tens = value / 10;      // 0–9   → A nibble

  // Write ones digit to B pins
  digitalWrite(B0, ones & 0x01);
  digitalWrite(B1, (ones >> 1) & 0x01);
  digitalWrite(B2, (ones >> 2) & 0x01);
  digitalWrite(B3, (ones >> 3) & 0x01);

  // Write tens digit to A pins
  digitalWrite(A0, tens & 0x01);
  digitalWrite(A1, (tens >> 1) & 0x01);
  digitalWrite(A2, (tens >> 2) & 0x01);
  digitalWrite(A3, (tens >> 3) & 0x01);
}

void setup() {
  Serial.begin(1000000);
  Serial.setTimeout(5);

  // configure pins
  pinMode(B0, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(B3, OUTPUT);

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  pinMode(SERVO_PIN, OUTPUT);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);


  displayNumber(-1);
}

void setLED(int r, int g, int b) {
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}

int display_delay_count = DISPLAY_DELAY_COUNT;

void loop() {

  while(!Serial.available()) {}
  String output = Serial.readString();
  String head = output.substring(0, 1);
  String data = output.substring(1);

  if (head == "d") {
    displayNumber(data.toInt());
  }
  else if (head == "l") {
    int red = data.substring(0, 3).toInt();
    int green = data.substring(3, 6).toInt();
    int blue = data.substring(6, 9).toInt();
    setLED(red, green, blue);
  }
  else if (head == "m") {
    int level = data.toInt();
    if (display_delay_count > 0) {
      setLED(0, level, 0);
      display_delay_count--;
    }
    else {
      setLED(0, level, 0);
      displayNumber(level * 100 / 255);
      display_delay_count = DISPLAY_DELAY_COUNT;
    }
  }
}

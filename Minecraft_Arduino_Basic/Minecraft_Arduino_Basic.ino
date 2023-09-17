#include "MCreatorLink.h"

void dataEvent(String command, String data) {
  // if you send a message from the Link API inside Minecraft with this format command?data
  // this function will be called when the message is received
  // you can then parse these messages inside this function and use them
  if(data.equals("ledOn")) {
    digitalWrite(13, HIGH);
  }
  else if (data.equals("ledOff")) {
    digitalWrite(13, LOW);
  }
}

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(5);
    MCreatorLink.setup(Serial, "Bruh Moment");
    MCreatorLink.setListener(dataEvent);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    MCreatorLink.loop();
}

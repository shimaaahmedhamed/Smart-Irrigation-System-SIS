#include <SoftwareSerial.h>
SoftwareSerial serial(25,26);
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}

void loop() { // run over and over
if (Serial.available()) {
  char x=Serial.read();
//Serial.write(x);
Serial.print(x);
}
}

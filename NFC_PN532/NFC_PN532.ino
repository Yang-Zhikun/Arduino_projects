#include <PN532.h>
#include <PN532_SWHSU.h>
#include <SoftwareSerial.h>

#define PN532_TX 2
#define PN532_RX 3

SoftwareSerial nfc(PN532_TX, PN532_RX);
const uint8_t wakeup[] = {0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03, 0xFD, 0xD4, 0x14, 0x01, 0x17, 0x00};


void setup() {
  Serial.begin(115200);
  nfc.begin(115200);
  nfc.write(wakeup, sizeof(wakeup));
  delay(1000);
  while (nfc.available()) {
    Serial.println(nfc.read());
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
#include <Arduino.h>
#line 1 "D:\\DevFiles\\Arduino\\Arduino_projects\\NFC_PN532\\NFC_PN532.ino"
#include <PN532_HSU.h>
#include <PN532.h>

PN532_HSU pn532hsu(Serial);
PN532 nfc(pn532hsu);

void setup(void)
{
    Serial.begin(115200);
    delay(100);
    Serial.println("Hello! PN532 HSU");

    nfc.begin();

    uint32_t versiondata = nfc.getFirmwareVersion();
    if (!versiondata) {
        Serial.println("Didn't find PN532 board");
        while (1);
    }
    Serial.print("Found chip PN532");
}

void loop() {
}

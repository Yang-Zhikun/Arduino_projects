#include<SoftwareSerial.h>

#define PN532_RX 2 // PN532 RX pin
#define PN532_TX 3 // PN532 TX pin
// SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic = false);
SoftwareSerial mySerial(PN532_TX, PN532_RX);

void setup(){
    Serial.begin(115200);
    mySerial.begin(115200); // Initialize SoftwareSerial at 115200 baud rate
    while (!mySerial) {
        Serial.println("Waiting for SoftwareSerial to be ready...");
    }
    Serial.println("SoftwareSerial PN532 ready");
    // Send a command to the PN532 to wake it up
    mySerial.print("55 55 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF 03 FD D4 14 01 17 00", HEX);
    // 等待PN532响应
    while (!mySerial.available()) {
        delay(10);
    }
    // 读取响应
    uint8_t response[16];
    mySerial.readBytes(response, 16);
    // 打印响应
    for (int i = 0; i < 16; i++) {
        Serial.print(response[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}

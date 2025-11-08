#include<HardwareSerial.h>
void setup(){
    Serial.begin(115200);
    pinMode(13, OUTPUT); //LED½Ó13
}
void loop(){
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
    Serial.println("Hello World!");
}
#include <Arduino.h>
#line 1 "D:\\DevFiles\\Arduino\\Arduino_projects\\LED-blink\\LED-blink.ino"
#include<HardwareSerial.h>
#line 2 "D:\\DevFiles\\Arduino\\Arduino_projects\\LED-blink\\LED-blink.ino"
void setup();
#line 6 "D:\\DevFiles\\Arduino\\Arduino_projects\\LED-blink\\LED-blink.ino"
void loop();
#line 2 "D:\\DevFiles\\Arduino\\Arduino_projects\\LED-blink\\LED-blink.ino"
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

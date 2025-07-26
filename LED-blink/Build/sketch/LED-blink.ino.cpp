#include <Arduino.h>
#line 1 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\LED-blink\\LED-blink.ino"
#line 1 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\LED-blink\\LED-blink.ino"
void setup();
#line 5 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\LED-blink\\LED-blink.ino"
void loop();
#line 1 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\LED-blink\\LED-blink.ino"
void setup(){
    Serial.begin(9600);
    pinMode(13, OUTPUT); //LED½Ó13
}
void loop(){
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
    Serial.println("Hello World!");
}

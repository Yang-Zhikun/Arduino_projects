#include <Arduino.h>
#line 1 "D:\\DevFiles\\Arduino\\Arduino_projects\\relay_test\\relay_test.ino"
#line 1 "D:\\DevFiles\\Arduino\\Arduino_projects\\relay_test\\relay_test.ino"
void setup();
#line 4 "D:\\DevFiles\\Arduino\\Arduino_projects\\relay_test\\relay_test.ino"
void loop();
#line 1 "D:\\DevFiles\\Arduino\\Arduino_projects\\relay_test\\relay_test.ino"
void setup(){
    pinMode(4, OUTPUT);
}
void loop(){
    digitalWrite(4, HIGH);
    delay(1000);
    digitalWrite(4, LOW);
    delay(1000);
}

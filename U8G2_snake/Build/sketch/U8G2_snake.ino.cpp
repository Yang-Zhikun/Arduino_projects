#include <Arduino.h>
#line 1 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\U8G2_snake.ino"
#include <U8glib.h>

U8GLIB_ST7920_128X64 u8g(8, 9, 10, 11); // E,RW,RS,RST

#line 5 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\U8G2_snake.ino"
void setup();
#line 9 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\U8G2_snake.ino"
void loop();
#line 5 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\U8G2_snake.ino"
void setup() {
  u8g.setRot180();
}

void loop() {
  u8g.firstPage();
  do {
    u8g.drawFrame(10,10,108,44);
    u8g.drawStr(20, 35, "Hello World!");
  } while(u8g.nextPage());
  delay(100);
}

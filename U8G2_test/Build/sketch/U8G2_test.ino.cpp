#include <Arduino.h>
#line 1 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
// 测试u8g2 128*64 屏幕
/**
 * 接线：
 *           128*64 屏幕              Arduino UNO
 *              GND -------------> GND
 *              VCC -------------> 5V
 *              RS  -------------> D10
 *              R/W -------------> D9
 *              E   -------------> D8
 *              PSB -------------> GND
 *              RST -------------> D11
 *              BLA -------------> 3.3V
 *              BLK -------------> GND
*/
#include <U8g2lib.h>

// 定义引脚
#define SCK 8  // 时钟
#define MOSI 9 // 数据
#define CS 10  // 片选
#define RESET 11 // 复位

// 初始化屏幕
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R2, SCK, MOSI, CS);

#line 26 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void setup();
#line 31 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void loop();
#line 26 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_simple1_tr);
}

void loop() {
  u8g2.firstPage();
  do {
    u8g2.drawStr(15, 15, "Hello, World!");
    u8g2.drawStr(30, 15, "你好");
  } while ( u8g2.nextPage() );
  delay(1000);
}

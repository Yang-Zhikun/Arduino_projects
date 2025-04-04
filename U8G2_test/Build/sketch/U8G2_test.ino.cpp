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
#include <U8glib.h>

// 调整引脚定义以匹配接线
U8GLIB_ST7920_128X64_1X u8g(/*sck(E)*/ 8, /*mosi(R/W)*/ 9, /*cs(RS)*/ 10); // 初始化屏幕

#line 20 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void setup();
#line 25 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void loop();
#line 20 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void setup() {
  u8g.begin(); // 初始化屏幕
  Serial.begin(9600); // 初始化串口
}

void loop() {
  u8g.firstPage(); // 开始绘制
  do {
    u8g.drawStr(0, 32, "Hello, World!"); // 打印字符串
    // 添加结束条件，绘制下一页
  } while (u8g.nextPage()); 
}

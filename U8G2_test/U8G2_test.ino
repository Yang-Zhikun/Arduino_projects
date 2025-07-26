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
#define CLK 8  // 时钟 E
#define MOSI 9 // 数据 R/W
#define CS 10  // 片选 RS
// #define RST 11 // 复位




/****************************************************************************************************
 * BufferDrawing模式
 * 注意初始化时候用      U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, SCK, MOSI, CS);
 ****************************************************************************************************/
// 初始化屏幕，尝试不同的旋转参数
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, CLK, MOSI, CS);

void setup(void)
{
  u8g2.begin(); // 初始化显示屏
  u8g2.setFont(u8g2_font_ncenB14_tr);
}


void loop()
{

  u8g2.clearBuffer();                 // 清空内部缓冲区
  u8g2.setFont(u8g2_font_ncenB08_tr); // 选择合适的字体
  u8g2.drawStr(0, 10, "Hello World!"); // 将内容写入内部缓冲区
  u8g2.sendBuffer(); // 将内部缓冲区内容传输到显示屏
  Serial.println("Display updated");

  delay(1000);
  Serial.println("Loop ended");
}






/*****************************************************************************************************
 * PageDrawing模式
 * 注意初始化时候用      U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, CLK, MOSI, CS);
 *****************************************************************************************************/
// U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, CLK, MOSI, CS);

// void setup(void)
// {
//   u8g2.begin(); // 初始化显示屏
//   u8g2.setFont(u8g2_font_ncenB14_tr);
// }

// void loop(void)
// {
//   u8g2.firstPage();
//   do
//   {
//     u8g2.drawStr(0, 24, "Hello World!");
//   } while (u8g2.nextPage());
//   delay(1000); // 延时1秒
// }
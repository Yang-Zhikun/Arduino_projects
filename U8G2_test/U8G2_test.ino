// ����u8g2 128*64 ��Ļ
/**
 * ���ߣ�
 *           128*64 ��Ļ              Arduino UNO
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

// ��������
#define CLK 8  // ʱ�� E
#define MOSI 9 // ���� R/W
#define CS 10  // Ƭѡ RS
// #define RST 11 // ��λ




/****************************************************************************************************
 * BufferDrawingģʽ
 * ע���ʼ��ʱ����      U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, SCK, MOSI, CS);
 ****************************************************************************************************/
// ��ʼ����Ļ�����Բ�ͬ����ת����
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, CLK, MOSI, CS);

void setup(void)
{
  u8g2.begin(); // ��ʼ����ʾ��
  u8g2.setFont(u8g2_font_ncenB14_tr);
}


void loop()
{

  u8g2.clearBuffer();                 // ����ڲ�������
  u8g2.setFont(u8g2_font_ncenB08_tr); // ѡ����ʵ�����
  u8g2.drawStr(0, 10, "Hello World!"); // ������д���ڲ�������
  u8g2.sendBuffer(); // ���ڲ����������ݴ��䵽��ʾ��
  Serial.println("Display updated");

  delay(1000);
  Serial.println("Loop ended");
}






/*****************************************************************************************************
 * PageDrawingģʽ
 * ע���ʼ��ʱ����      U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, CLK, MOSI, CS);
 *****************************************************************************************************/
// U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, CLK, MOSI, CS);

// void setup(void)
// {
//   u8g2.begin(); // ��ʼ����ʾ��
//   u8g2.setFont(u8g2_font_ncenB14_tr);
// }

// void loop(void)
// {
//   u8g2.firstPage();
//   do
//   {
//     u8g2.drawStr(0, 24, "Hello World!");
//   } while (u8g2.nextPage());
//   delay(1000); // ��ʱ1��
// }
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
#define SCK 8  // ʱ��
#define MOSI 9 // ����
#define CS 10  // Ƭѡ
#define RESET 11 // ��λ

// ��ʼ����Ļ
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R2, SCK, MOSI, CS);

void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_simple1_tr);
}

void loop() {
  u8g2.firstPage();
  do {
    u8g2.drawStr(15, 15, "Hello, World!");
    u8g2.drawStr(30, 15, "���");
  } while ( u8g2.nextPage() );
  delay(1000);
}
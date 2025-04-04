#include <Arduino.h>
#line 1 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
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
#include <U8glib.h>

// �������Ŷ�����ƥ�����
U8GLIB_ST7920_128X64_1X u8g(/*sck(E)*/ 8, /*mosi(R/W)*/ 9, /*cs(RS)*/ 10); // ��ʼ����Ļ

#line 20 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void setup();
#line 25 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void loop();
#line 20 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void setup() {
  u8g.begin(); // ��ʼ����Ļ
  Serial.begin(9600); // ��ʼ������
}

void loop() {
  u8g.firstPage(); // ��ʼ����
  do {
    u8g.drawStr(0, 32, "Hello, World!"); // ��ӡ�ַ���
    // ��ӽ���������������һҳ
  } while (u8g.nextPage()); 
}

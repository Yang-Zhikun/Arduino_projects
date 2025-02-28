/**
 * ���ܣ��������ģ�飬��ȡ�����źţ�����python�ű�������ȡ���ĺ����źŷ��ͱ��浽IR_data.txt��
 * Ӳ�����������ģ�飬����ң����
 * ���ߣ�    �������ģ��    Arduino
 *           GND             GND
 *           VCC             5V
 *            S(data)         D13
 */

#include <IRremote.h> // ���������

#define IR_RECEIVER_PIN 13 // ������������ӵ���������

IRrecv IR_receiver; // �����������������

void setup() {
  Serial.begin(9600); // ��ʼ������ͨ��
  IR_receiver.begin(IR_RECEIVER_PIN); // ��ʼ�����������
  Serial.println("IRreceiver begin"); // ��ӡ��ʾ��Ϣ
  IR_receiver.enableIRIn(); // ���ú��������
}
 
void loop() {
  if(IR_receiver.decode()){
    Serial.print(IR_receiver.decodedIRData.protocol); // ��ӡ�����źŵ�Э��
    Serial.print("|0x");
    Serial.println(IR_receiver.decodedIRData.command, HEX); // ��ӡ�����źŵ�����
    IR_receiver.resume(); // ����������һ�������ź�
  }
}
 
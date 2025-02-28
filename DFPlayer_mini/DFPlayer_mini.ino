/**
 * ���ܣ�DFPlayer Miniģ����Ƴ���ͨ������ָ�arduino���п���
 * ����Ӳ����DFPlayer Miniģ�顢�����������������
 * ���ߣ�DFPlayer Mini      Arduino
 *              RX  <---��---> 2
 *              TX  <-220ŷ����-> 3
 *              BUSY <---��---> 4
 *              GND <---��---> GND
 *               VCC <---��---> 5V
 *         ������         DFplayer Mini
 *             +  <---��---> SPK1
 *             -  <---��---> SPK2
 *        ���������         Arduino
 *             GND <---��---> GND
 *            VCC <---��---> 5V
 *            OUT <---��---> 13
 *
 */

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <IRremote.h>
#include "IR_commands.h"

 // ����DFPlayer Mini���� 
#define DFPLAYER_RX 2 
#define DFPLAYER_TX 3
#define DFPLAYER_BUSY 4
DFRobotDFPlayerMini mp3player; // ����DFPlayer Mini���� 
bool is_pause; // �Ƿ�����ͣ״̬

// ��ʼ������ 
SoftwareSerial softSerial(DFPLAYER_RX, DFPLAYER_TX);

// ����������������
#define IR_RECEIVER_PIN 13 // ������������ӵ���������
IRrecv IR_receiver; // �����������������



void setup() {
  // ��ʼ��Ӳ���� 
  Serial.begin(9600);

  // ��ʼ�����������
  IR_receiver.begin(IR_RECEIVER_PIN); // ��ʼ�����������
  Serial.println("IRreceiver begin"); // ��ӡ��ʾ��Ϣ
  IR_receiver.enableIRIn(); // ���ú��������

  // ��ʼ������ 
  softSerial.begin(9600);
  // ��ʼ��DFPlayer Mini 
  while (!mp3player.begin(softSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }
  Serial.println(F("DFPlayer Mini online."));

  // ���ó�ʼ����0-30
  mp3player.volume(1);
  mp3player.play(1078);  // �ӵ�1078�׸�����ʼѭ������
  mp3player.enableLoopAll(); //loop all mp3 files.
  is_pause = false;

  delay(1000);
}


void loop() {

  // ��ȡDFplayer mini��״̬����������Ҳ�������ͣ�����Զ�������һ��
  if (digitalRead(DFPLAYER_BUSY) == HIGH && !is_pause) {
    delay(600); // �ȵȴ���������ǲ�æ���Ų�����һ��
    if (digitalRead(DFPLAYER_BUSY) == HIGH) {
      mp3player.next();
      Serial.println("next");
    }
  }

  // ���������� 
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    processSerialCommand(command);
  }

  // �����������
  if (IR_receiver.decode()) {
    processIRCommand(IR_receiver.decodedIRData.protocol, IR_receiver.decodedIRData.command);
    delay(50); // ��ʱ, ��ֹ�ظ����պ����ź�
    IR_receiver.resume(); // ����������һ�������ź�
  }
}





/**
 * ����������
 * @param command ���������ַ���
 */
void processSerialCommand(String command) {
  // ���� start
  if (command == "start") {
    mp3player.start();
    Serial.println("start");
    is_pause = false;
  }
  // ��ͣ pause
  else if (command == "pause") {
    mp3player.pause();
    Serial.println("pause");
    is_pause = true;
  }
  // ��һ�� next
  else if (command == "next") {
    mp3player.next();
    Serial.println("next");
  }
  // ��һ�� prev
  else if (command == "prev") {
    mp3player.previous();
    Serial.println("prev");
  }
  // ��ָ����Ŀ���� play+�ո�+��λ������Ŀ��
  else if (command.startsWith("play ")) {
    int num = command.substring(5).toInt();  // ��ȡ��Ŀ��
    mp3player.play(num);  // ��ָ����Ŀ����
    Serial.println("Playing file: " + String(num));
  }

  // �������� +
  else if (command == "+") {
    if (mp3player.readVolume() < 30) {
      mp3player.volumeUp();
      Serial.println("Volume set to: " + String(mp3player.readVolume()));
    }
    else {
      Serial.println("Volume is max");
    }
  }
  // ��С���� -
  else if (command == "-") {
    if (mp3player.readVolume() > 0) {
      mp3player.volumeDown();
      Serial.println("Volume set to: " + String(mp3player.readVolume()));
    }
    else {
      Serial.println("Volume is min");
    }
  }
  // δ֪����
  else {
    Serial.println("Unknown Serial command");
  }
}



unsigned long lastMillis; // �ϴΰ������ּ���ʱ��


/**
 * ��������ź�
 * @param command �����ź�����
 * @param protocol �����ź�Э��

 */
void processIRCommand(decode_type_t protocol, uint16_t command) {
  // �������֧�ֵ�Э�飬����Ը�����
  if (protocol != IR_PROTOCOL) {
    return;
  }

  // ����0
  if (command == NUM_0) {
    lastMillis = millis();

  }
  // ��һ��
  if (command == PREV) {
    mp3player.previous();
    Serial.println("prev");
  }
  // ��һ��
  else if (command == NEXT) {
    mp3player.next();
    Serial.println("next");
  }
  // ����/��ͣ
  else if (command == START_PAUSE) {
    // ��ͣ
    if (digitalRead(DFPLAYER_BUSY) == LOW) {
      mp3player.pause();
      Serial.println("pause");
      is_pause = true;
    }
    // ����
    else {
      mp3player.start();
      Serial.println("play");
      is_pause = false;
    }
  }
  // ������
  else if (command == VOL_DOWN) {
    if (mp3player.readVolume() > 0) {
      mp3player.volumeDown();
      Serial.println("Volume set to: " + String(mp3player.readVolume()));
    }
    else {
      Serial.println("Volume is min");
    }
  }
  // ������
  else if (command == VOL_UP) {
    if (mp3player.readVolume() < 30) {
      mp3player.volumeUp();
      Serial.println("Volume set to: " + String(mp3player.readVolume()));
    }
    else {
      Serial.println("Volume is max");
    }
  }


  // δ֪����
  else {
    Serial.println("Unknown IR command");
  }
}




/************************************************************************************* */
#define BUTTON_PIN 2  // ���谴�����ӵ���������2
#define DEBOUNCE_DELAY 100  // ȥ�����ӳ٣���λ������
#define TIMEOUT 2000  // ��ʱ����ʱʱ�䣬��λ������

unsigned long lastDebounceTime = 0;  // �ϴ�ȥ����ʱ��
unsigned long lastInputTime = 0;  // �ϴ���Ч����ʱ��
bool hasNewInput = false;  // �Ƿ����µİ�������
String inputBuffer = "";  // ���뻺����


void loop2() {
    unsigned long currentTime = millis();  // ��ȡ��ǰʱ��

    // ��ⰴ������
    if (digitalRead(BUTTON_PIN) == LOW) {  // ����������
        if (currentTime - lastDebounceTime > DEBOUNCE_DELAY) {  // ȥ����
            lastDebounceTime = currentTime;  // ����ȥ����ʱ��
            if (currentTime - lastInputTime > TIMEOUT) {  // ��ʱ����ʱ
                // �������뻺�����е�����
                processInput(inputBuffer);
                inputBuffer = "";  // ������뻺����
            } else {
                hasNewInput = true;  // ������µİ�������
                lastInputTime = currentTime;  // ������Ч����ʱ��
                inputBuffer += "1";  // ���谴����������1������ʵ������޸�
            }
        }
    } else {
        hasNewInput = false;  // ����δ���£�������������
    }

    // ���û���µİ��������Ҽ�ʱ��������ʱ��������Ӷ�����߼�������ʾ��ǰ���룩
}

void processInput(String input) {
    // �����ﴦ����������֣���������Ƶ����
    Serial.println("Input received: " + input);  // ��������ڣ������ã�
}
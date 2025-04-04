#include <Arduino.h>
#line 1 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\DFPlayer_mini\\DFPlayer_mini.ino"
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


#line 40 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\DFPlayer_mini\\DFPlayer_mini.ino"
void setup();
#line 56 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\DFPlayer_mini\\DFPlayer_mini.ino"
void loop();
#line 88 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\DFPlayer_mini\\DFPlayer_mini.ino"
void initDFPlayerMini();
#line 109 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\DFPlayer_mini\\DFPlayer_mini.ino"
void processSerialCommand(String command);
#line 183 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\DFPlayer_mini\\DFPlayer_mini.ino"
void processIRCommand(decode_type_t protocol, uint16_t command);
#line 40 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\DFPlayer_mini\\DFPlayer_mini.ino"
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
  initDFPlayerMini();
}

void loop() {
  // ��ȡDFplayer mini��״̬����������Ҳ�������ͣ�����Զ�������һ��
  if (digitalRead(DFPLAYER_BUSY) == HIGH && !is_pause) {
    Serial.println("Busy pin is HIGH and not paused, waiting...");
    delay(600); // �ȵȴ���������ǲ�æ���Ų�����һ��
    if (digitalRead(DFPLAYER_BUSY) == HIGH) {
      Serial.println("Busy pin is still HIGH, playing next song");
      mp3player.next();
      delay(600); // �ȴ�������һ��
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
 * ��ʼ��DFPlayer Mini
*/
void initDFPlayerMini() {
  while (!mp3player.begin(softSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }
  Serial.println(F("DFPlayer Mini online."));

  // ���ó�ʼ����0-30
  mp3player.volume(1);
  mp3player.play(1078);  // �ӵ�1078�׸�����ʼѭ������
  is_pause = false;

  delay(1000);
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



// �����������ڼ�¼���µ��������С��ϴΰ��µ�ʱ��
String enteredDigits = "";
unsigned long lastPressTime = 0;
const unsigned long MAX_TIME_INTERVAL = 1000; // ���ʱ��������λ������

// ����һ��ӳ����洢ÿ�����ֶ�Ӧ�ĺ�����
const uint16_t digitIRCodes[10] = {
    NUM_0, NUM_1, NUM_2, NUM_3, NUM_4,
    NUM_5, NUM_6, NUM_7, NUM_8, NUM_9
};

/**
 * ��������ź�
 * @param command �����ź�����
 * @param protocol �����ź�Э��
 */
void processIRCommand(decode_type_t protocol, uint16_t command) {
  // �������֧�ֵ�Э�飬����Ը�����
  if (protocol != IR_PROTOCOL) {
    Serial.println("Received unsupported IR protocol.");
    return;
  }

  unsigned long currentTime = millis();
  Serial.print("Current time: ");
  Serial.println(currentTime);
  Serial.print("Last press time: ");
  Serial.println(lastPressTime);

  // ��ȫ��ʱ�����㷽��
  unsigned long timeDifference = currentTime - lastPressTime;
  Serial.print("Time difference: ");
  Serial.println(timeDifference);

  // �������ְ���
  bool isDigitKey = false;
  for (int i = 0; i < 10; i++) {
    if (command == digitIRCodes[i]) {
      isDigitKey = true;
      Serial.print("Received digit key: ");
      Serial.println(i);
      // ����Ƿ񳬹����ʱ����
      if (timeDifference > MAX_TIME_INTERVAL) {
        if (enteredDigits.length() > 0) {
          int trackNumber = enteredDigits.toInt();
          Serial.print("Entered digits: ");
          Serial.println(enteredDigits);
          Serial.print("Track number: ");
          Serial.println(trackNumber);
          if (trackNumber > 0) {
            Serial.print("Trying to play track: ");
            Serial.println(trackNumber);
            // ����ָ����Ŀ�ĸ���
            mp3player.play(trackNumber);

          }
          else {
            Serial.println("Invalid track number.");
          }
        }
        else {
          Serial.println("No digits entered previously.");
        }
        // ���������������
        enteredDigits = "";
      }
      // ���°��µ�������ӵ������������������
      enteredDigits += String(i);
      lastPressTime = currentTime;
      break;
    }
  }

  if (!isDigitKey) {
    // �����ʱ��������������������Ƿ���Ч
    if (enteredDigits.length() > 0 && timeDifference > MAX_TIME_INTERVAL) {
      int trackNumber = enteredDigits.toInt();
      Serial.print("Entered digits: ");
      Serial.println(enteredDigits);
      Serial.print("Track number: ");
      Serial.println(trackNumber);
      if (trackNumber > 0) {
        Serial.print("Trying to play track: ");
        Serial.println(trackNumber);
        // ����ָ����Ŀ�ĸ���
        mp3player.play(trackNumber);

      }
      else {
        Serial.println("Invalid track number.");
      }
      // ������ɺ��������������������
      enteredDigits = "";
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
}

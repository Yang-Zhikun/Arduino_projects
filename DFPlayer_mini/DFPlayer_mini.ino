/**
 * 功能：DFPlayer Mini模块控制程序，通过发送指令到arduino进行控制
 * 所需硬件：DFPlayer Mini模块、扬声器、红外接收器
 * 接线：DFPlayer Mini      Arduino
 *              RX  <-------> 3
 *              TX  <-------> 2
 *              BUSY <-------> 4
 *              GND <-------> GND
 *               VCC <-------> 5V
 *         扬声器         DFplayer Mini
 *             +  <-------> SPK1
 *             -  <-------> SPK2
 *        红外接收器         Arduino
 *             GND <-------> GND
 *            VCC <-------> 5V
 *            OUT <-------> 13
 * 指令：见下方函数
 */

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <IRremote.h>
#include "IR_commands.h"

// 定义DFPlayer Mini引脚
#define DFPLAYER_RX 2
#define DFPLAYER_TX 3
#define DFPLAYER_BUSY 4
DFRobotDFPlayerMini mp3player; // 定义DFPlayer Mini对象
bool is_pause;                 // 是否处于暂停状态

// 初始化软串口
SoftwareSerial softSerial(DFPLAYER_RX, DFPLAYER_TX);

// 定义红外接收器引脚
#define IR_RECEIVER_PIN 13 // 红外接收器连接的数字引脚

void setup()
{
  // 初始化硬串口
  Serial.begin(115200);

  // 初始化红外接收器
  IrReceiver.begin(IR_RECEIVER_PIN);  /**************** 用自带的irReceiver对象!!!!!!! */
  Serial.println("IRreceiver begin"); // 打印提示信息

  // 初始化软串口
  softSerial.begin(9600); // DFPlayer Mini默认波特率为9600

  // 初始化DFPlayer Mini
  initDFPlayerMini();
}

void loop()
{
  // 读取DFplayer mini的状态，如果空闲且不是在暂停，则自动播放下一曲
  if (digitalRead(DFPLAYER_BUSY) == HIGH && !is_pause)
  {
    Serial.println("Busy pin is HIGH and not paused, waiting...");
    delay(600); // 先等待，如果还是不忙，才播放下一曲
    if (digitalRead(DFPLAYER_BUSY) == HIGH)
    {
      Serial.println("Busy pin is still HIGH, playing next song");
      mp3player.next();
      delay(600); // 等待播放下一曲
    }
  }

  // 处理串口命令
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');
    processSerialCommand(command);
  }

  // 处理红外命令
  if (IrReceiver.decode())
  {
    processIRCommand(IrReceiver.decodedIRData.protocol, IrReceiver.decodedIRData.command);
    delay(50);           // 延时, 防止重复接收红外信号
    IrReceiver.resume(); // 继续接收下一个红外信号
  }
}

/**
 * 初始化DFPlayer Mini
 */
void initDFPlayerMini()
{
  while (!mp3player.begin(softSerial, /*isACK = */ true, /*doReset = */ true))
  { // Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }
  Serial.println(F("DFPlayer Mini online."));

  // 设置初始音量
  mp3player.volume(1);
  mp3player.play(1078); // 从第1078首歌曲开始循环播放
  mp3player.start();

  is_pause = false;

  // 等待1秒，确保DFPlayer Mini初始化完成
  delay(1000);
}

/**
 * 处理串口命令
 * @param command 串口命令字符串
 */
void processSerialCommand(String command)
{
  // 播放 start
  if (command == "start")
  {
    mp3player.start();
    Serial.println("start");
    is_pause = false;
  }
  // 暂停 pause
  else if (command == "pause")
  {
    mp3player.pause();
    Serial.println("pause");
    is_pause = true;
  }
  // 下一曲 next
  else if (command == "next")
  {
    mp3player.next();
    Serial.println("next");
  }
  // 上一曲 prev
  else if (command == "prev")
  {
    mp3player.previous();
    Serial.println("prev");
  }
  // 按指定曲目播放 play+空格+四位数字曲目号
  else if (command.startsWith("play "))
  {
    int num = command.substring(5).toInt(); // 获取曲目号
    mp3player.play(num);                    // 按指定曲目播放
    Serial.println("Playing file: " + String(num));
  }

  // 调大音量 +
  else if (command == "+")
  {
    if (mp3player.readVolume() < 30)
    {
      mp3player.volumeUp();
      Serial.println("Volume set to: " + String(mp3player.readVolume()));
    }
    else
    {
      Serial.println("Volume is max");
    }
  }
  // 调小音量 -
  else if (command == "-")
  {
    if (mp3player.readVolume() > 0)
    {
      mp3player.volumeDown();
      Serial.println("Volume set to: " + String(mp3player.readVolume()));
    }
    else
    {
      Serial.println("Volume is min");
    }
  }
  // 未知命令
  else
  {
    Serial.println("Unknown Serial command");
  }
}

// 定义一个映射表，存储每个数字对应的红外码
const uint16_t digitIRCodes[10] = {
    NUM_0, NUM_1, NUM_2, NUM_3, NUM_4,
    NUM_5, NUM_6, NUM_7, NUM_8, NUM_9};

int digitsInput = 0;        // 存储输入的数字

/**
 * 处理红外信号
 * @param command 红外信号命令
 * @param protocol 红外信号协议
 */
void processIRCommand(decode_type_t protocol, uint16_t command)
{
  // 如果不是支持的协议，则忽略该命令
  if (protocol != IR_PROTOCOL)
  {
    Serial.println("Received unsupported IR protocol.");
    return;
  }

  // 数字按键0-9
  for (int i = 0; i <= 9; i++){
    if (command == digitIRCodes[i]){
      Serial.println("Digit pressed: " + String(i));
      // 存储输入的数字
      digitsInput = digitsInput * 10 + i;
    }
  }
  // EQ键，播放输入的数字对应的歌曲
  if (command == EQ)
  {
    // 播放输入的数字对应的歌曲
    mp3player.play(digitsInput);
    Serial.println("Playing file: " + String(digitsInput));
    // 重置输入的数字
    digitsInput = 0;
  }
  

  // 上一曲
  if (command == PREV)
  {
    mp3player.previous();
    Serial.println("prev");
  }
  // 下一曲
  else if (command == NEXT)
  {
    mp3player.next();
    Serial.println("next");
  }
  // 播放/暂停
  else if (command == START_PAUSE)
  {
    // 暂停
    if (digitalRead(DFPLAYER_BUSY) == LOW)
    {
      mp3player.pause();
      Serial.println("pause");
      is_pause = true;
    }
    // 播放
    else
    {
      mp3player.start();
      Serial.println("play");
      is_pause = false;
    }
  }
  // 音量减
  else if (command == VOL_DOWN)
  {
    if (mp3player.readVolume() > 0)
    {
      mp3player.volumeDown();
      Serial.println("Volume set to: " + String(mp3player.readVolume()));
    }
    else
    {
      Serial.println("Volume is min");
    }
  }
  // 音量加
  else if (command == VOL_UP)
  {
    if (mp3player.readVolume() < 30)
    {
      mp3player.volumeUp();
      Serial.println("Volume set to: " + String(mp3player.readVolume()));
    }
    else
    {
      Serial.println("Volume is max");
    }
  }

  // 未知命令
  else
  {
    Serial.println("Unknown IR command");
  }
}
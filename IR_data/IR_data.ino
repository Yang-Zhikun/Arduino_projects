/**
 * 功能：红外接收模块，读取红外信号，运行python脚本，将读取到的红外信号发送保存到IR_data.txt中
 * 硬件：红外接收模块，红外遥控器
 * 接线：    红外接收模块    Arduino
 *           GND             GND
 *           VCC             5V
 *            S(data)         D13
 */

#include <IRremote.h> // 包含红外库

#define IR_RECEIVER_PIN 13 // 红外接收器连接的数字引脚

IRrecv IR_receiver; // 创建红外接收器对象

void setup() {
  Serial.begin(9600); // 初始化串口通信
  IR_receiver.begin(IR_RECEIVER_PIN); // 初始化红外接收器
  Serial.println("IRreceiver begin"); // 打印提示信息
  IR_receiver.enableIRIn(); // 启用红外接收器
}
 
void loop() {
  if(IR_receiver.decode()){
    Serial.print(IR_receiver.decodedIRData.protocol); // 打印红外信号的协议
    Serial.print("|0x");
    Serial.println(IR_receiver.decodedIRData.command, HEX); // 打印红外信号的命令
    IR_receiver.resume(); // 继续接收下一个红外信号
  }
}
 
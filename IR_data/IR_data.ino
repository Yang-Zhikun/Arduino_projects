/**
 * 功能：红外接收模块，读取红外信号，运行python脚本，将读取到的红外信号发送保存到IR_data.txt中
 * 硬件：红外接收模块，红外遥控器
 * 接线：    红外接收模块    Arduino
 *           GND             GND
 *           VCC             5V
 *            S(data)         D2  (更换为D2引脚避免冲突)
 */

#include <IRremote.h> // 包含红外库

#define IR_RECEIVER_PIN 13 // 更换为D2引脚避免与板载LED冲突



void setup() {
  Serial.begin(115200); // 初始化串口通信
  IrReceiver.begin(IR_RECEIVER_PIN); /**************** 用自带的irReceiver对象!!!!!!! */
  Serial.println("IRreceiver begin"); // 打印提示信息
}
 
void loop() {
  if(IrReceiver.decode()) { // 检测到红外信号
    Serial.println("IRreceiver decode"); // 打印提示信息
    Serial.print(IrReceiver.decodedIRData.protocol); // 打印红外信号的协议
    Serial.print("|0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX); // 打印红外信号的命令
    IrReceiver.resume(); // 继续接收下一个红外信号
  }
}
#line 1 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\README.md"
# U8G2贪吃蛇游戏

## 项目概述
基于Arduino开发平台，使用ST7920液晶屏和红外遥控实现的经典贪吃蛇游戏。项目采用U8g2图形库进行屏幕驱动，通过红外接收器实现方向控制。

## 硬件需求
- Arduino Uno开发板
- ST7920 128x64液晶屏
- 红外接收器 (VS1838B)
- 杜邦线若干

## 接线说明
```
液晶屏接线：
SCK   -> Arduino D8
MOSI  -> Arduino D9
CS    -> Arduino D10
RESET -> Arduino D11

红外接收器：
SIG -> Arduino D13
VCC -> 5V
GND -> GND
```

## 软件依赖
- [U8g2库](https://github.com/olikraus/u8g2)
- [IRremote库](https://github.com/Arduino-IRremote/Arduino-IRremote)

安装方法：
1. Arduino IDE -> 工具 -> 管理库
2. 搜索安装 U8g2 和 IRremote

## 编译上传
1. 选择开发板类型：工具 -> 开发板 -> Arduino Uno
2. 选择端口
3. 点击"上传"按钮编译并烧录程序

## 游戏操作
- 方向键控制：
  ▲ 0x45 - 上
  ▼ 0x46 - 下
  ? 0x47 - 左
  ? 0x44 - 右
- 得分规则：每吃1个食物得10分
- 游戏结束：蛇头碰撞身体时死循环

## 项目结构
```
U8G2_snake/
├── U8G2_snake.ino    # 主程序
├── IR_commands.h     # 红外指令定义
└── README.md         # 项目文档
```
1. 使用环形缓冲区管理蛇身坐标
2. 实现移动方向控制与碰撞检测
3. 支持蛇身自动生长机制

2. **Food类**：
   - 随机生成有效食物位置
   - 自动避开蛇身位置
   - 碰撞检测处理

3. **显示系统**：
   - 使用U8g2库驱动ST7920液晶
   - 实时刷新游戏画面（100ms/帧）
   - 分数显示系统

## 开发环境配置
1. 安装Arduino IDE 1.8.x以上版本
2. 通过库管理器安装：
```arduino
U8g2lib@2.32.0
IRremote@3.6.1
```
3. 选择开发板：Arduino Uno
4. 端口设置：根据实际COM端口选择
5. 编译上传：使用4800波特率进行烧录

## 故障排查
- 屏幕无显示：检查复位引脚连接
- 红外不响应：确认接收器供电正常
- 程序卡死：检查碰撞检测逻辑
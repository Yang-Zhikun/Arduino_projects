#include <Arduino.h>
#line 1 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\U8G2_snake.ino"
#include <U8g2lib.h>
#include <EEPROM.h>
#include "IR_commands.h"
// 定义引脚
/*
 * 硬件接线说明
 * ST7920液晶屏四线控制：
 * SCK  -  Arduino 8 脚（时钟线）
 * MOSI -  Arduino 9 脚（数据线）
 * CS   -  Arduino 10 脚（片选）
 * RESET-  Arduino 11 脚（复位）
 * 
 * 红外接收器：
 * 信号线 - Arduino 13 脚
 * 电源正极 - 5V
 * 电源负极 - GND
 */
#define SCK 8  // 时钟
#define MOSI 9 // 数据
#define CS 10  // 片选
#define RESET 11 // 复位

// 初始化屏幕
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R2, SCK, MOSI, CS);

// 控制引脚定义
#include <IRremote.h>

#define IR_PIN 13
IRrecv irrecv(IR_PIN);
decode_results results;

struct Point { int x; int y; };

class Snake {
private:
  bool paused = false;  // 新增暂停状态标志
  Point body[100];
  int head = 0;
public:
  int getHeadIndex() { return head; }
  int tail = 0;
  int direction = 0;
  int growCounter = 0;
  int score = 0;

public:
  int getTail() { return tail; }


  void addScore(int value) { score += value; }
  int getScore() { return score; }

public:
  Snake() {
    body[head] = {64, 32};
  }

  /**
 * @brief 控制蛇的移动逻辑
 * @details 根据当前方向计算新头部位置，更新环形缓冲区索引
 * 处理生长计数器并移动尾部位置
 */
void move() {
    // 移动头部
    Point newHead = body[head];
    switch(direction) {
      case 0: newHead.x += 2; break;
      case 1: newHead.y += 2; break;
      case 2: newHead.x -= 2; break;
      case 3: newHead.y -= 2; break;
    }
    
    // 环形缓冲区处理
    head = (head + 1) % 100;
    body[head] = newHead;
    
    if(growCounter <= 0) {
      tail = (tail + 1) % 100;
    } else {
      growCounter--;
    }
  }

  /**
 * @brief 设置蛇的移动方向
 * @param newDir 新方向值（0-右,1-下,2-左,3-上）
 * @note 禁止180度转向
 */
void setDirection(int newDir) { 
    if(abs(direction - newDir) != 2) {
      direction = newDir;
    }
  }



  /**
 * @brief 检测蛇头与身体的碰撞
 * @return true 发生自碰撞，false 未碰撞
 */
bool checkSelfCollision() {
    for(int i = tail; i != head; i = (i+1)%100) {
    Point segment = body[i];
      if(body[head].x == segment.x && body[head].y == segment.y) {
        return true;
      }
    }
    return false;
  }
  
  // 添加获取长度和身体段的方法
  int getLength() { return (head >= tail) ? (head - tail +1) : (100 - tail + head +1); }
  Point getHead() { return body[head]; }
  Point getSegment(int index) { return body[index]; }
  void togglePause() { paused = !paused; }
  bool isPaused() { return paused; }
};

class Food {
private:
  Point position;

public:
  /**
 * @brief 生成新食物位置
 * @param snake 当前蛇对象引用
 * @details 使用随机数生成有效位置，最多尝试20次
 */
void generate(Snake &snake) {
    randomSeed(analogRead(A0));
    int maxAttempts = 20;
    
    do {
      position.x = random(0, 64) * 2;
      position.y = random(0, 32) * 2;
    } while(!isValidPosition(snake) && maxAttempts-- > 0);
}

Point getPosition() {
    return this->position;
}

  /**
 * @brief 验证食物位置有效性
 * @param snake 当前蛇对象引用
 * @return true 位置有效，false 无效
 */
bool isValidPosition(Snake &snake) {
    // 检查边界和蛇身碰撞
    bool inBounds = (position.x >= 0 && position.x < 128 &&
                   position.y >= 0 && position.y < 64);
    bool onSnake = false;
    int headIndex = snake.getHeadIndex();
    for(int i = snake.getTail(); i != headIndex; i = (i+1)%100) {
      if(position.x == snake.getSegment(i).x && position.y == snake.getSegment(i).y) {
        onSnake = true;
        break;
      }
    }
    return inBounds && !onSnake;
  }

  /**
 * @brief 检测蛇头与食物的碰撞
 * @param snake 当前蛇对象引用
 * @return true 发生碰撞，false 未碰撞
 */
bool checkCollision(Snake &snake) {
    Point head = snake.getHead();
    return (head.x == this->position.x && head.y == this->position.y);
  }
};














// 游戏对象实例化
Snake snakeObj;
Food foodObj;
// 删除残留的全局数组
// 原snake[]数组已被Snake类中的body数组替代





/**
 * @brief 处理红外遥控输入
 * @details 解析红外信号并更新蛇的运动方向
 * 方向键对应：0x45-上，0x46-下，0x47-左，0x44-右
 */
#line 203 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\U8G2_snake.ino"
void handleInput();
#line 216 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\U8G2_snake.ino"
void setup();
#line 237 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\U8G2_snake.ino"
void loop();
#line 270 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\U8G2_snake.ino"
void checkCollisions();
#line 305 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\U8G2_snake.ino"
void drawGame();
#line 203 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\U8G2_snake.ino"
void handleInput() {
  if (irrecv.decode(&results)) {
    switch(results.value) {
      case CH_ADD: snakeObj.setDirection(0); break;  // 右
      case CH: snakeObj.setDirection(1); break;    // 下
      case CH_MINUS: snakeObj.setDirection(2); break; // 左
      case PREV: snakeObj.setDirection(3); break;   // 上
      case START_PAUSE: snakeObj.togglePause(); break;      // 暂停/继续
    }
    irrecv.resume();
  }
}

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.setFont(u8g_font_6x10);
  irrecv.enableIRIn();
  foodObj.generate(snakeObj);

  // 显示初始化测试图案
  u8g2.firstPage();
  do {
    u8g2.drawStr(20, 30, "Init Success!");
    u8g2.drawFrame(40, 40, 20, 20);
  } while(u8g2.nextPage());
  delay(2000);
}

/**
 * @brief 游戏主循环
 * @details 负责游戏状态更新、画面渲染和输入处理
 * 每100ms刷新一次游戏画面
 */
void loop() {
  static uint32_t lastTime = 0;
  static int frameCount = 0;
  
  handleInput();
  checkCollisions();
  
  // 在drawGame()中添加暂停状态显示
  if(!snakeObj.isPaused()) {
    snakeObj.move();
  }
  
  // 更新游戏画面
  u8g2.firstPage();
  do {
    drawGame();
  } while(u8g2.nextPage());
  
  // 帧率统计
  frameCount++;
  if(millis() - lastTime >= 1000) {
    Serial.print("FPS: ");
    Serial.println(frameCount);
    frameCount = 0;
    lastTime = millis();
  }
  
  delay(100);
}
/**
 * @brief 碰撞检测总控函数
 * @details 检测食物碰撞和自碰撞，触发游戏结束逻辑
 */
void checkCollisions() {
  static bool gameOver = false;
  
  if(foodObj.checkCollision(snakeObj)) {
    snakeObj.addScore(10);
    foodObj.generate(snakeObj);
  }
  
  if(snakeObj.checkSelfCollision() && !gameOver) {
    Serial.println("GAME OVER!");
    gameOver = true;
  }

  // 新增边界检查
  Point headPos = snakeObj.getHead();
  if((headPos.x < 0 || headPos.x >= 126) || (headPos.y < 0 || headPos.y >= 62)) {
    Serial.println("WALL CRASH!");
    gameOver = true;
  }

  if(gameOver) {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g_font_7x14B);
      u8g2.drawStr(30, 30, "GAME OVER");
      u8g2.drawStr(20, 50, "Press RESTART");
    } while(u8g2.nextPage());
    while(1) { delay(100); } // 保持显示但允许其他操作
  }
}

/**
 * @brief 绘制游戏画面
 * @details 包含蛇身绘制、食物绘制和分数显示
 */
void drawGame() {
  u8g2.setFont(u8g_font_6x10);
  
  // 绘制蛇身
  for(int i=0, idx=snakeObj.getTail(); i<snakeObj.getLength(); i++, idx=(idx+1)%100) {
    Point seg = snakeObj.getSegment(idx);
    u8g2.drawBox(seg.x, seg.y, 2, 2);
  }
  
  // 绘制食物
  Point foodPos = foodObj.getPosition();
  u8g2.drawFrame(foodPos.x, foodPos.y, 2, 2);
  
  // 显示分数
  char scoreStr[16];
  sprintf(scoreStr, "Score: %d", snakeObj.getScore());
  u8g2.drawStr(0, 12, scoreStr);
  
  // 在drawGame()中添加暂停状态显示
  if(snakeObj.isPaused()) {
    u8g2.setFont(u8g_font_7x14B);
    u8g2.drawStr(40, 40, "PAUSE");
  }
}

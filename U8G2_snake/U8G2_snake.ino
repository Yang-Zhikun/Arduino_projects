#include <U8glib.h>
#include <EEPROM.h>

U8GLIB_ST7920_128X64_1X u8g(/*sck(E)*/ 10, /*mosi(R/W)*/ 9, /*cs(RS)*/ 8); // 初始化屏幕

// 控制引脚定义
#include <IRremote.h>

#define IR_PIN 6
IRrecv irrecv(IR_PIN);
decode_results results;

struct Point { int x; int y; };

class Snake {
private:
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

  void setDirection(int newDir) { 
    if(abs(direction - newDir) != 2) {
      direction = newDir;
    }
  }



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
  int getLength() { return (head >= tail) ? (head - tail) : (100 - tail + head); }
  Point getHead() { return body[head]; }
  Point getSegment(int index) { return body[index]; }
};

class Food {
private:
  Point position;

public:
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





void handleInput() {
  if (irrecv.decode(&results)) {
    switch(results.value) {
      case 0x45: snakeObj.setDirection(3); break;  // 上
      case 0x46: snakeObj.setDirection(1); break;  // 下
      case 0x47: snakeObj.setDirection(2); break;  // 左
      case 0x44: snakeObj.setDirection(0); break;  // 右
    }
    irrecv.resume();
  }
}

void setup() {
  u8g.begin();
  u8g.setFont(u8g_font_6x10);
  irrecv.enableIRIn();
  foodObj.generate(snakeObj);

  // 显示初始化测试图案
  u8g.firstPage();
  do {
    u8g.drawStr(20, 30, "Init Success!");
    u8g.drawFrame(40, 40, 20, 20);
  } while(u8g.nextPage());
  delay(2000);
}

void loop() {
  // 临时显示测试图案
  u8g.firstPage();
  do {
    u8g.drawStr(0, 12, "TEST PATTERN");
    u8g.drawHLine(0, 16, 128);
    for(int x=0; x<128; x+=8) {
      u8g.drawPixel(x, 20);
    }
  } while(u8g.nextPage());
  
  while(1); // 保持测试画面
}













void checkCollisions() {
  if(foodObj.checkCollision(snakeObj)) {
    snakeObj.addScore(10);
    foodObj.generate(snakeObj);
  }
  if(snakeObj.checkSelfCollision()) {
    // 游戏结束逻辑
    while(1); // 暂时死循环
  }
}

void drawGame() {
  u8g.setFont(u8g_font_6x10);
  
  // 绘制蛇身
  for(int i=0; i<snakeObj.getLength(); i++) {
    Point seg = snakeObj.getSegment(i);
    u8g.drawBox(seg.x, seg.y, 2, 2);
  }
  
  // 绘制食物
  Point foodPos = foodObj.getPosition();
  u8g.drawFrame(foodPos.x, foodPos.y, 2, 2);
  
  // 显示分数
  char scoreStr[16];
  sprintf(scoreStr, "Score: %d", snakeObj.getScore());
  u8g.drawStr(0, 12, scoreStr);
}
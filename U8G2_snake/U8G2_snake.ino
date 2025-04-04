#include <U8glib.h>
#include <EEPROM.h>

U8GLIB_ST7920_128X64_1X u8g(/*sck(E)*/ 10, /*mosi(R/W)*/ 9, /*cs(RS)*/ 8); // ��ʼ����Ļ

// �������Ŷ���
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
    // �ƶ�ͷ��
    Point newHead = body[head];
    switch(direction) {
      case 0: newHead.x += 2; break;
      case 1: newHead.y += 2; break;
      case 2: newHead.x -= 2; break;
      case 3: newHead.y -= 2; break;
    }
    
    // ���λ���������
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
  
  // ��ӻ�ȡ���Ⱥ�����εķ���
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
    // ���߽��������ײ
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














// ��Ϸ����ʵ����
Snake snakeObj;
Food foodObj;
// ɾ��������ȫ������
// ԭsnake[]�����ѱ�Snake���е�body�������





void handleInput() {
  if (irrecv.decode(&results)) {
    switch(results.value) {
      case 0x45: snakeObj.setDirection(3); break;  // ��
      case 0x46: snakeObj.setDirection(1); break;  // ��
      case 0x47: snakeObj.setDirection(2); break;  // ��
      case 0x44: snakeObj.setDirection(0); break;  // ��
    }
    irrecv.resume();
  }
}

void setup() {
  u8g.begin();
  u8g.setFont(u8g_font_6x10);
  irrecv.enableIRIn();
  foodObj.generate(snakeObj);

  // ��ʾ��ʼ������ͼ��
  u8g.firstPage();
  do {
    u8g.drawStr(20, 30, "Init Success!");
    u8g.drawFrame(40, 40, 20, 20);
  } while(u8g.nextPage());
  delay(2000);
}

void loop() {
  // ��ʱ��ʾ����ͼ��
  u8g.firstPage();
  do {
    u8g.drawStr(0, 12, "TEST PATTERN");
    u8g.drawHLine(0, 16, 128);
    for(int x=0; x<128; x+=8) {
      u8g.drawPixel(x, 20);
    }
  } while(u8g.nextPage());
  
  while(1); // ���ֲ��Ի���
}













void checkCollisions() {
  if(foodObj.checkCollision(snakeObj)) {
    snakeObj.addScore(10);
    foodObj.generate(snakeObj);
  }
  if(snakeObj.checkSelfCollision()) {
    // ��Ϸ�����߼�
    while(1); // ��ʱ��ѭ��
  }
}

void drawGame() {
  u8g.setFont(u8g_font_6x10);
  
  // ��������
  for(int i=0; i<snakeObj.getLength(); i++) {
    Point seg = snakeObj.getSegment(i);
    u8g.drawBox(seg.x, seg.y, 2, 2);
  }
  
  // ����ʳ��
  Point foodPos = foodObj.getPosition();
  u8g.drawFrame(foodPos.x, foodPos.y, 2, 2);
  
  // ��ʾ����
  char scoreStr[16];
  sprintf(scoreStr, "Score: %d", snakeObj.getScore());
  u8g.drawStr(0, 12, scoreStr);
}
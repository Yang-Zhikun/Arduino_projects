#include <Arduino.h>
#line 1 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_snake\\U8G2_snake.ino"
#include <U8g2lib.h>
#include <EEPROM.h>
#include "IR_commands.h"
// ��������
/*
 * Ӳ������˵��
 * ST7920Һ�������߿��ƣ�
 * SCK  -  Arduino 8 �ţ�ʱ���ߣ�
 * MOSI -  Arduino 9 �ţ������ߣ�
 * CS   -  Arduino 10 �ţ�Ƭѡ��
 * RESET-  Arduino 11 �ţ���λ��
 * 
 * �����������
 * �ź��� - Arduino 13 ��
 * ��Դ���� - 5V
 * ��Դ���� - GND
 */
#define SCK 8  // ʱ��
#define MOSI 9 // ����
#define CS 10  // Ƭѡ
#define RESET 11 // ��λ

// ��ʼ����Ļ
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R2, SCK, MOSI, CS);

// �������Ŷ���
#include <IRremote.h>

#define IR_PIN 13
IRrecv irrecv(IR_PIN);
decode_results results;

struct Point { int x; int y; };

class Snake {
private:
  bool paused = false;  // ������ͣ״̬��־
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
 * @brief �����ߵ��ƶ��߼�
 * @details ���ݵ�ǰ���������ͷ��λ�ã����»��λ���������
 * �����������������ƶ�β��λ��
 */
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

  /**
 * @brief �����ߵ��ƶ�����
 * @param newDir �·���ֵ��0-��,1-��,2-��,3-�ϣ�
 * @note ��ֹ180��ת��
 */
void setDirection(int newDir) { 
    if(abs(direction - newDir) != 2) {
      direction = newDir;
    }
  }



  /**
 * @brief �����ͷ���������ײ
 * @return true ��������ײ��false δ��ײ
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
  
  // ��ӻ�ȡ���Ⱥ�����εķ���
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
 * @brief ������ʳ��λ��
 * @param snake ��ǰ�߶�������
 * @details ʹ�������������Чλ�ã���ೢ��20��
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
 * @brief ��֤ʳ��λ����Ч��
 * @param snake ��ǰ�߶�������
 * @return true λ����Ч��false ��Ч
 */
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

  /**
 * @brief �����ͷ��ʳ�����ײ
 * @param snake ��ǰ�߶�������
 * @return true ������ײ��false δ��ײ
 */
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





/**
 * @brief �������ң������
 * @details ���������źŲ������ߵ��˶�����
 * �������Ӧ��0x45-�ϣ�0x46-�£�0x47-��0x44-��
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
      case CH_ADD: snakeObj.setDirection(0); break;  // ��
      case CH: snakeObj.setDirection(1); break;    // ��
      case CH_MINUS: snakeObj.setDirection(2); break; // ��
      case PREV: snakeObj.setDirection(3); break;   // ��
      case START_PAUSE: snakeObj.togglePause(); break;      // ��ͣ/����
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

  // ��ʾ��ʼ������ͼ��
  u8g2.firstPage();
  do {
    u8g2.drawStr(20, 30, "Init Success!");
    u8g2.drawFrame(40, 40, 20, 20);
  } while(u8g2.nextPage());
  delay(2000);
}

/**
 * @brief ��Ϸ��ѭ��
 * @details ������Ϸ״̬���¡�������Ⱦ�����봦��
 * ÿ100msˢ��һ����Ϸ����
 */
void loop() {
  static uint32_t lastTime = 0;
  static int frameCount = 0;
  
  handleInput();
  checkCollisions();
  
  // ��drawGame()�������ͣ״̬��ʾ
  if(!snakeObj.isPaused()) {
    snakeObj.move();
  }
  
  // ������Ϸ����
  u8g2.firstPage();
  do {
    drawGame();
  } while(u8g2.nextPage());
  
  // ֡��ͳ��
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
 * @brief ��ײ����ܿغ���
 * @details ���ʳ����ײ������ײ��������Ϸ�����߼�
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

  // �����߽���
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
    while(1) { delay(100); } // ������ʾ��������������
  }
}

/**
 * @brief ������Ϸ����
 * @details ����������ơ�ʳ����ƺͷ�����ʾ
 */
void drawGame() {
  u8g2.setFont(u8g_font_6x10);
  
  // ��������
  for(int i=0, idx=snakeObj.getTail(); i<snakeObj.getLength(); i++, idx=(idx+1)%100) {
    Point seg = snakeObj.getSegment(idx);
    u8g2.drawBox(seg.x, seg.y, 2, 2);
  }
  
  // ����ʳ��
  Point foodPos = foodObj.getPosition();
  u8g2.drawFrame(foodPos.x, foodPos.y, 2, 2);
  
  // ��ʾ����
  char scoreStr[16];
  sprintf(scoreStr, "Score: %d", snakeObj.getScore());
  u8g2.drawStr(0, 12, scoreStr);
  
  // ��drawGame()�������ͣ״̬��ʾ
  if(snakeObj.isPaused()) {
    u8g2.setFont(u8g_font_7x14B);
    u8g2.drawStr(40, 40, "PAUSE");
  }
}

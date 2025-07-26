#include <Arduino.h>
#line 1 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
// 测试u8g2 128*64 屏幕
/**
 * 接线：
 *           128*64 屏幕              Arduino UNO
 *              GND -------------> GND
 *              VCC -------------> 5V
 *              RS  -------------> D10
 *              R/W -------------> D9
 *              E   -------------> D8
 *              PSB -------------> GND
 *              RST -------------> D11
 *              BLA -------------> 3.3V
 *              BLK -------------> GND
 */
#include <U8g2lib.h>

// 定义引脚
#define CLK 8  // 时钟 E
#define MOSI 9 // 数据 R/W
#define CS 10  // 片选 RS
// #define RST 11 // 复位




/****************************************************************************************************
 * BufferDrawing模式
 * 注意初始化时候用      U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, SCK, MOSI, CS);
 ****************************************************************************************************/
// 初始化屏幕，尝试不同的旋转参数
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, CLK, MOSI, CS);

#line 33 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void setup(void);
#line 75 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void draw(struct menu_state *state);
#line 97 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void to_right(struct menu_state *state);
#line 115 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void to_left(struct menu_state *state);
#line 135 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
uint8_t towards_int16(int16_t *current, int16_t dest);
#line 150 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
uint8_t towards(struct menu_state *current, struct menu_state *destination);
#line 166 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void loop();
#line 33 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\U8G2_test.ino"
void setup(void)
{
  u8g2.begin(); // 初始化显示屏
  u8g2.setFont(u8g2_font_ncenB14_tr);
}

struct menu_entry_type
{
  const uint8_t *font;
  uint16_t icon;
  const char *name;
};

struct menu_state
{
  int16_t menu_start;		/* in pixel */
  int16_t frame_position;		/* in pixel */
  uint8_t position;			/* position, array index */
};

/*
  Icon configuration
  Width and height must match the icon font size
  GAP: Space between the icons
  BGAP: Gap between the display border and the cursor.
*/
#define ICON_WIDTH 32
#define ICON_HEIGHT 32
#define ICON_GAP 4
#define ICON_BGAP 16
#define ICON_Y 32+ ICON_GAP

struct menu_entry_type menu_entry_list[] =
{
  { u8g2_font_open_iconic_embedded_4x_t, 65, "Clock Setup"},
  { u8g2_font_open_iconic_embedded_4x_t, 66, "Gear Game"},
  { u8g2_font_open_iconic_embedded_4x_t, 67, "Flash Light"},
  { u8g2_font_open_iconic_embedded_4x_t, 68, "Home"},
  { u8g2_font_open_iconic_embedded_4x_t, 72, "Configuration"},
  { NULL, 0, NULL } 
};

void draw(struct menu_state *state)
{
  int16_t x;
  uint8_t i;
  x = state->menu_start;
  i = 0;
  while( menu_entry_list[i].icon > 0 )  
  {
    if ( x >= -ICON_WIDTH && x < u8g2.getDisplayWidth() )
    {
      u8g2.setFont(menu_entry_list[i].font);
      u8g2.drawGlyph(x, ICON_Y, menu_entry_list[i].icon );
    }
    i++;
    x += ICON_WIDTH + ICON_GAP;
  }
  u8g2.drawFrame(state->frame_position-1, ICON_Y-ICON_HEIGHT-1, ICON_WIDTH+2, ICON_WIDTH+2);
  u8g2.drawFrame(state->frame_position-2, ICON_Y-ICON_HEIGHT-2, ICON_WIDTH+4, ICON_WIDTH+4);
  u8g2.drawFrame(state->frame_position-3, ICON_Y-ICON_HEIGHT-3, ICON_WIDTH+6, ICON_WIDTH+6);
}


void to_right(struct menu_state *state)
{
  if ( menu_entry_list[state->position+1].font != NULL )
  {
    if ( (int16_t)state->frame_position+ 2*(int16_t)ICON_WIDTH + (int16_t)ICON_BGAP < (int16_t)u8g2.getDisplayWidth() )
    {
      state->position++;
      state->frame_position += ICON_WIDTH + (int16_t)ICON_GAP;
    }
    else
    {
      state->position++;      
      state->frame_position = (int16_t)u8g2.getDisplayWidth() - (int16_t)ICON_WIDTH - (int16_t)ICON_BGAP;
      state->menu_start = state->frame_position - state->position*((int16_t)ICON_WIDTH + (int16_t)ICON_GAP);
    }
  }
}

void to_left(struct menu_state *state)
{
  if ( state->position > 0 )
  {
    if ( (int16_t)state->frame_position >= (int16_t)ICON_BGAP+(int16_t)ICON_WIDTH+ (int16_t)ICON_GAP )
    {
      state->position--;
      state->frame_position -= ICON_WIDTH + (int16_t)ICON_GAP;
    }    
    else
    {
      state->position--; 
      state->frame_position = ICON_BGAP;
      state->menu_start = state->frame_position - state->position*((int16_t)ICON_WIDTH + (int16_t)ICON_GAP);
      
    }
  }
}


uint8_t towards_int16(int16_t *current, int16_t dest)
{
  if ( *current < dest )
  {
    (*current)++;
    return 1;
  }
  else if ( *current > dest )
  {
    (*current)--;
    return 1;
  }
  return 0;
}

uint8_t towards(struct menu_state *current, struct menu_state *destination)
{
  uint8_t r = 0;
  r |= towards_int16( &(current->frame_position), destination->frame_position);
  r |= towards_int16( &(current->frame_position), destination->frame_position);
  r |= towards_int16( &(current->menu_start), destination->menu_start);
  r |= towards_int16( &(current->menu_start), destination->menu_start);
  return r;
}



struct menu_state current_state = { ICON_BGAP, ICON_BGAP, 0 };
struct menu_state destination_state = { ICON_BGAP, ICON_BGAP, 0 };


void loop()
{

  int8_t event;

  do
  {
    u8g2.clearBuffer();
    draw(&current_state);  
    u8g2.setFont(u8g2_font_helvB10_tr);  
    u8g2.setCursor((u8g2.getDisplayWidth()-u8g2.getStrWidth(menu_entry_list[destination_state.position].name))/2,u8g2.getDisplayHeight()-5);
    u8g2.print(menu_entry_list[destination_state.position].name);    
    u8g2.sendBuffer();
    delay(10);
    event = u8g2.getMenuEvent();
    if ( event == U8X8_MSG_GPIO_MENU_NEXT )
      to_right(&destination_state);
    if ( event == U8X8_MSG_GPIO_MENU_PREV )
      to_left(&destination_state);
    if ( event == U8X8_MSG_GPIO_MENU_SELECT )
    {
      u8g2.setFont(u8g2_font_helvB10_tr);  
      u8g2.userInterfaceMessage("Selection:", menu_entry_list[destination_state.position].name, "", " Ok ");
    }
  } while ( towards(&current_state, &destination_state) );
}






/*****************************************************************************************************
 * PageDrawing模式
 * 注意初始化时候用      U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, CLK, MOSI, CS);
 *****************************************************************************************************/
// U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, CLK, MOSI, CS);

// void setup(void)
// {
//   u8g2.begin(); // 初始化显示屏
//   u8g2.setFont(u8g2_font_ncenB14_tr);
// }

// void loop(void)
// {
//   u8g2.firstPage();
//   do
//   {
//     u8g2.drawStr(0, 24, "Hello World!");
//   } while (u8g2.nextPage());
//   delay(1000); // 延时1秒
// }

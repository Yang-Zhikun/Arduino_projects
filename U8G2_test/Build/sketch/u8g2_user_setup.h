#line 1 "D:\\DevFiles\\ArduinoFiles\\Arduino_projects\\U8G2_test\\u8g2_user_setup.h"
// 禁用硬件 SPI、硬件 I2C 和 ESPI
#define U8G2_NO_HW_SPI
#define U8G2_NO_HW_I2C
#define U8G2_NO_ESPI

// 只启用 ST7920 驱动
#define U8G2_ST7920_128X64_1_SW_SPI_ENABLED

// // 禁用所有字体
// #define U8G2_FONT_SECTION_ENABLE 0

// // 只启用需要的字体，这里以 3x5 字体为例，按需修改
// #define U8G2_FONT_3X5IM_MR_ENABLE 1

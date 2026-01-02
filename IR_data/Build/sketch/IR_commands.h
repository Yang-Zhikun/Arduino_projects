#line 1 "D:\\DevFiles\\Arduino\\Arduino_projects\\IR_data\\IR_commands.h"
#ifndef IR_COMMANDS_H
#define IR_COMMANDS_H


#define IR_PROTOCOL 8 // 红外信号的协议(NEC)

#define CH_MINUS 0x45      // CH-
#define CH 0x46            // CH
#define CH_ADD 0x47        // CH+
#define PREV 0x44          // 上一曲
#define NEXT 0x40          // 下一曲
#define PLAY_PAUSE 0x43    // 播放/暂停
#define VOL_MINUS 0x07     // VOL
#define VOL_PLUS 0x15      // VOL+
#define EQ 0x09            // EQ
#define NUM_0 0x16       // 数字0
#define NUM_100 0x19       // 数字100+
#define NUM_200 0x0D       // 数字200+
#define NUM_1 0x0C         // 数字1
#define NUM_2 0x18         // 数字2
#define NUM_3 0x5E         // 数字3
#define NUM_4 0x08         // 数字4
#define NUM_5 0x1C         // 数字5
#define NUM_6 0x5A         // 数字6
#define NUM_7 0x42         // 数字7
#define NUM_8 0x52         // 数字8
#define NUM_9 0x4A         // 数字9


#endif
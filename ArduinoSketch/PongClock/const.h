#ifndef CONST_H
#define CONST_H

#define BOARD_VERSION 154

#define DISPLAY_WIDTH 32
#define DISPLAY_HEIGHT 24
#define MAX7219_COUNT 12

#if BOARD_VERSION >= 158 
#define MAX7219_CLK 6
#define MAX7219_CS 5
#define MAX7219_DIN 7

#define SW1 3
#define SW2 4
#define LED 2

#endif

#if BOARD_VERSION == 156
#define MAX7219_CLK 7
#define MAX7219_CS 6
#define MAX7219_DIN 5

#define SW1 3
#define SW2 4
#define LED 2

#endif

#if BOARD_VERSION == 154
#define MAX7219_CLK 9
#define MAX7219_CS 8
#define MAX7219_DIN 2

#define ROT_SW 3
#define ROT_A 4
#define ROT_B 5
#define ROTARY_ENABLE

#define SW1 ROT_SW

#define LED 2
#endif




#endif //CONST_H

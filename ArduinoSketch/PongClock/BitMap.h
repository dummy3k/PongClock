#ifndef BITMAP_H
#define BITMAP_H

#include <Arduino.h>
#include "const.h"

class Bitmap {
private:
  byte stream[8][MAX7219_COUNT];
  
public:
  Bitmap() {
    memset(stream, 0, 8 * MAX7219_COUNT);
  }

  void setPixel(uint8_t source_x, uint8_t source_y) {
    uint8_t x = 0;
    uint8_t y = 0;

    if (source_y >= 16) {
        x = 0;
    } else if (source_y >= 8) {
        x = 4;
    } else {
        x = 8;
    }
        
    x += source_x / 8;
    y = source_y % 8;
    byte v = 1 << 7 - source_x % 8;

    stream[y][x] |= v;
  }

  void sendData() {
    for (byte row = 0; row < 8; row++) {
      digitalWrite(MAX7219_CS, LOW);
      for (int i=0; i<MAX7219_COUNT; i++) {
        shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, 0x01 + row);
        shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, stream[row][i]);
      }
      digitalWrite(MAX7219_CS, HIGH);
    }
    
  }

  void digit(uint8_t source_x, uint8_t source_y, uint8_t v) {
    /*
     *  101   # ### ### # # ### ### ### ### ### ###
     *  3 2   #   #   # # # #   #     # # # # # # #
     *  454   # ### ### ### ### ###   # ### ### # #
     *  6 7   # #     #   #   # # #   # # #   # # #
     *  ###   # ### ###   # ### ###   # ###   # ###
     */

    switch (v) {
      case 0:
        setPixel(source_x, source_y);
        setPixel(source_x + 1, source_y);
        setPixel(source_x + 2, source_y);

        setPixel(source_x, source_y + 1);
        setPixel(source_x + 2, source_y + 1);
        
        setPixel(source_x, source_y + 2);
        setPixel(source_x + 2, source_y + 2);
        
        setPixel(source_x, source_y + 3);
        setPixel(source_x + 2, source_y + 3);
        
        setPixel(source_x, source_y + 4);
        setPixel(source_x + 1, source_y + 4);
        setPixel(source_x + 2, source_y + 4);
        break;

      case 1:
        setPixel(source_x + 2, source_y);
        setPixel(source_x + 2, source_y + 1);
        setPixel(source_x + 2, source_y + 2);
        setPixel(source_x + 2, source_y + 3);
        setPixel(source_x + 2, source_y + 4);
        break;

      case 2:
        setPixel(source_x, source_y);
        setPixel(source_x + 1, source_y);
        setPixel(source_x + 2, source_y);

        setPixel(source_x + 2, source_y + 1);
        
        setPixel(source_x, source_y + 2);
        setPixel(source_x + 1, source_y + 2);
        setPixel(source_x + 2, source_y + 2);
        
        setPixel(source_x, source_y + 3);
        
        setPixel(source_x, source_y + 4);
        setPixel(source_x + 1, source_y + 4);
        setPixel(source_x + 2, source_y + 4);
        break;
        
      case 3:
        setPixel(source_x, source_y);
        setPixel(source_x + 1, source_y);
        setPixel(source_x + 2, source_y);

        setPixel(source_x + 2, source_y + 1);
        
        setPixel(source_x, source_y + 2);
        setPixel(source_x + 1, source_y + 2);
        setPixel(source_x + 2, source_y + 2);
        
        setPixel(source_x + 2, source_y + 3);
        
        setPixel(source_x, source_y + 4);
        setPixel(source_x + 1, source_y + 4);
        setPixel(source_x + 2, source_y + 4);
        break;
        
      case 4:
        setPixel(source_x, source_y);
        setPixel(source_x + 2, source_y);

        setPixel(source_x, source_y + 1);
        setPixel(source_x + 2, source_y + 1);
        
        setPixel(source_x, source_y + 2);
        setPixel(source_x + 1, source_y + 2);
        setPixel(source_x + 2, source_y + 2);
        
        setPixel(source_x + 2, source_y + 3);
        
        setPixel(source_x + 2, source_y + 4);
        break;
        
      case 5:
        setPixel(source_x, source_y);
        setPixel(source_x + 1, source_y);
        setPixel(source_x + 2, source_y);

        setPixel(source_x, source_y + 1);
        
        setPixel(source_x, source_y + 2);
        setPixel(source_x + 1, source_y + 2);
        setPixel(source_x + 2, source_y + 2);
        
        setPixel(source_x + 2, source_y + 3);
        
        setPixel(source_x, source_y + 4);
        setPixel(source_x + 1, source_y + 4);
        setPixel(source_x + 2, source_y + 4);
        break;
        
      case 6:
        setPixel(source_x, source_y);
        setPixel(source_x + 1, source_y);
        setPixel(source_x + 2, source_y);

        setPixel(source_x, source_y + 1);
        
        setPixel(source_x, source_y + 2);
        setPixel(source_x + 1, source_y + 2);
        setPixel(source_x + 2, source_y + 2);
        
        setPixel(source_x, source_y + 3);
        setPixel(source_x + 2, source_y + 3);
        
        setPixel(source_x, source_y + 4);
        setPixel(source_x + 1, source_y + 4);
        setPixel(source_x + 2, source_y + 4);
        break;
        

      case 7:
        setPixel(source_x, source_y);
        setPixel(source_x + 1, source_y);
        setPixel(source_x + 2, source_y);

        setPixel(source_x + 2, source_y + 1);
        setPixel(source_x + 2, source_y + 2);
        setPixel(source_x + 2, source_y + 3);
        setPixel(source_x + 2, source_y + 4);

        break;
        
      case 8:
        setPixel(source_x, source_y);
        setPixel(source_x + 1, source_y);
        setPixel(source_x + 2, source_y);

        setPixel(source_x, source_y + 1);
        setPixel(source_x + 2, source_y + 1);
        
        setPixel(source_x, source_y + 2);
        setPixel(source_x + 1, source_y + 2);
        setPixel(source_x + 2, source_y + 2);
        
        setPixel(source_x, source_y + 3);
        setPixel(source_x + 2, source_y + 3);
        
        setPixel(source_x, source_y + 4);
        setPixel(source_x + 1, source_y + 4);
        setPixel(source_x + 2, source_y + 4);
        break;

      case 9:
        setPixel(source_x, source_y);
        setPixel(source_x + 1, source_y);
        setPixel(source_x + 2, source_y);

        setPixel(source_x, source_y + 1);
        setPixel(source_x + 2, source_y + 1);
        
        setPixel(source_x, source_y + 2);
        setPixel(source_x + 1, source_y + 2);
        setPixel(source_x + 2, source_y + 2);
        
        setPixel(source_x + 2, source_y + 3);
        
        setPixel(source_x + 2, source_y + 4);
        break;


                
    }
  }
};

#endif

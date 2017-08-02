#include <limits.h>
#include <Wire.h>
#include "bitmap.h"
#include "const.h"
//#include "Timer.h"
#include "DateTime.h"

//Timer t;
//time_t bootTime;

void initialise_MAX7219() {
  digitalWrite(MAX7219_CS, HIGH);
  pinMode(MAX7219_DIN, OUTPUT);
  pinMode(MAX7219_CS, OUTPUT);
  pinMode(MAX7219_CLK, OUTPUT);

  output_all(0x0c, 0x01); //shutdown register - normal operation
  delay(1);
  
  output_all(0x0f, 0x00); //display test register - test mode off
  output_all(0x0b, 0x07); //scan limit register - display digits 0 thru 7
  output_all(0x0a, 0x00); //intensity register - min brightness
  //output_all(0x0a, 0x0f); //intensity register - max brightness
  output_all(0x09, 0x00); //decode mode register - no decode

  for (byte addr = 0x01; addr < 0x09; addr++) {
    output_all(addr, 0x00);
  }
  
  //output_all(0x02, 0x01);
  
}



struct Vector {
  double x;
  double y;

  Vector(double x, double y) {
    this->x = x;
    this->y = y;
  }
  double length() {
    return sqrt(x * x + y * y);
  }

  Vector normalize() {
    double len = length();
    return Vector(x / len, y / len);
  }
};

bool setup_done = false;


byte serial_get() {
  while (Serial.available() == 0) {
    delay(1);
  }
  return Serial.read();
}

byte debug_mode = false;
bool slow_mode = false;

typedef unsigned long my_time_t;

unsigned long time_delta(unsigned long start, unsigned long now) {
  if (now >= start) {
    return (now - start);
  } else {
    return (ULONG_MAX - start) + now;
  }
}


struct Paddle {
  Vector pos;

  void track(int y) {
    if (pos.y > y && pos.y > 2) {
      pos.y--;
    } else if (pos.y < y && pos.y < DISPLAY_HEIGHT - 3) {
      pos.y++;
    }
  }

  void avoid(int y) {
    if (y < DISPLAY_HEIGHT / 2) {
      track(y + 4);
    } else {
      track(y - 4);
    }
  }

  void draw(Bitmap& bmp) {
    for (int i=pos.y - 2; i <= pos.y + 2; i++) {
      bmp.setPixel(pos.x, i);
    }
  }

  bool hitTest(int y) {
    return (y >= pos.y - 2 && y <= pos.y + 2);
  }
  
};

struct GameState {
  Vector start_pos = {0, 0};
  Vector impulse = {0, 0};
  Vector last_pos = {0, 0};

  my_time_t start;
  my_time_t round_start;
  my_time_t round_length = 60000;
  byte score_hour;
  byte score_minute;
  
  Paddle leftPaddle  = {Vector(1, DISPLAY_HEIGHT / 2)};
  Paddle rightPaddle = {Vector(DISPLAY_WIDTH - 2, DISPLAY_HEIGHT / 2)};
  
  GameState() {
    //restart();
  }
  
  void restart() {
    start_pos = {DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2};
    impulse = Vector(random(1, 5), random(1, 5));
    if (random(0, 2) > 0) impulse.x *= -1;
    if (random(0, 2) > 0) impulse.y *= -1;
    impulse = impulse.normalize();

    if (!slow_mode) {
      impulse.x *= 10;
      impulse.y *= 10;
    }

    DateTime now = getTime();
    Serial.println(now.toString());
    score_hour = now.hour;
    score_minute = now.minute;
    /*
    Serial.print(score_hour);
    Serial.print(' ');
    Serial.println(score_minute);
    */

    start = millis();
    round_start = millis();
    round_length = (60 - (my_time_t)now.second) * 1000;

    Serial.print(F("round_length: "));
    Serial.println(round_length);

  }

  void loop() {
    double t = time_delta(start, millis());
    t /= 1000;

    if (slow_mode) {
      Serial.print(F("t: "));
      Serial.println(t);
    }
  
    Vector pos_t(start_pos.x + impulse.x * t,
                 start_pos.y + impulse.y * t);
  
    if (slow_mode) {
      Serial.print(F("pos_t: "));
      Serial.print(pos_t.x);
      Serial.print(' ');
      Serial.println(pos_t.y);
    }
  
    if (pos_t.y < 0 || pos_t.y >= DISPLAY_HEIGHT) {
      impulse.y *= -1;
      start_pos = last_pos;
      start = millis();
      return;
    } else if (impulse.x < 0 && pos_t.x >= 1 && pos_t.x <= 2 && leftPaddle.hitTest(pos_t.y)) {
      impulse.x *= -1;
      start_pos = last_pos;
      start = millis();
      return;
    } else if (impulse.x > 0 && pos_t.x >= DISPLAY_WIDTH - 2 && pos_t.x <= DISPLAY_WIDTH - 1 && rightPaddle.hitTest(pos_t.y)) {
      impulse.x *= -1;
      start_pos = last_pos;
      start = millis();
      return;
    } else if (pos_t.x < 0 || pos_t.x >= DISPLAY_WIDTH) {
      restart();
      return;
    }
    
    Bitmap bmp;
    bmp.setPixel(pos_t.x, pos_t.y);

    /*
    Paddle* targetPaddle;
    if (impulse.x > 0) {
      targetPaddle = &rightPaddle;
    } else {
      targetPaddle = &leftPaddle;
    }
    */

    
    if (time_delta(round_start, millis()) < round_length) {
      if (impulse.x > 0) {
        rightPaddle.track(pos_t.y);
      } else {
        leftPaddle.track(pos_t.y);
      }
    } else {
      if (impulse.x > 0) {
        if (score_minute == 59) {
          rightPaddle.avoid(pos_t.y);
        } else {
          rightPaddle.track(pos_t.y);
        }
      } else {
        if (score_minute != 59) {
          leftPaddle.avoid(pos_t.y);
        } else {
          leftPaddle.track(pos_t.y);
        }
      }
    }

    /*
    targetPaddle->avoid(pos_t.y);
    */
    
    leftPaddle.draw(bmp);
    rightPaddle.draw(bmp);

    bmp.digit(8, 18, score_hour / 10);
    bmp.digit(12, 18, score_hour % 10);

    bmp.digit(17, 18, score_minute / 10);
    bmp.digit(21, 18, score_minute % 10);
    
    /*
    paddle_left_y = pos_t.y;
    paddle_right_y = pos_t.y;
    
    for (int i=paddle_left_y - 2; i <= paddle_left_y + 2; i++) {
      bmp.setPixel(1, i);
    }
    for (int i=paddle_right_y - 2; i <= paddle_right_y + 2; i++) {
      bmp.setPixel(30, i);
    }
    */
    
    bmp.sendData();
  
    last_pos = pos_t;

    if (slow_mode) {
      delay(1000);
    }
    
  }


  
} game_state;

void setup() {
  initialise_MAX7219();
  Wire.begin();

  Serial.begin(9600);
  //delay(1000);
  
  Serial.println(F("PongClock v1.54"));
  Serial.println(F(__DATE__));
  Serial.println(F(__TIME__));

  randomSeed(analogRead(0));
  Serial.println(F("READY"));
  
  setup_done = true;
  game_state.restart();

  displayTime();  
  /*
  setDS3231time(30,22,15,4,26,11,14);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  bootTime = getTime();

  Serial.print(F("Boot time: "));
  Serial.println(bootTime.toString());

**********


  Vector v(3, 4);
  if (v.x != 3) Serial.println(__LINE__);
  if (v.y != 4) Serial.println(__LINE__);
  if (v.length() != 5) Serial.println(__LINE__);
  if (v.normalize().length() != 1) Serial.println(__LINE__);
  Vector v2 = {127, 127} ;
  if (v2.length() != 180) Serial.println(__LINE__);
  Serial.println(v2.length());

  //1, 4, 9, 16

**********
  
  */
  

}


void loop() {

  game_state.loop();  
  
  
  /*
  Serial.println(F(__TIME__));
  delay(1000);
  displayTime();
  delay(1000);
  for (int y = 0; y < 24; y++) {
    for (int x = 0; x < 32; x++) {
      Bitmap bmp;
      bmp.setPixel(x, y);
      bmp.sendData();
    }
  }
  */
  
  handle_serial();
  
}

void handle_serial() {
  /*
   * Output to all MAX7219
   * 0x01 0x?? 0x??                 
   * 
   * DMA
   * 0x02 <0x?? 0x??>{MAX7219_COUNT}
   * 
   * Buffered Memory
   * 0x03 <0x??>{MAX7219_COUNT*8}
   * 
   * RLE
   * 0x04 <0x??>{?}
   * 
   * Set Time
   * $H23
   * $M59
   * $S59
   * 
   * Debug Mode
   * 0xFF 0x01
   */
  DateTime now;
  while (Serial.available() > 0) {
    byte op_code = Serial.read();
    switch (op_code) {
      case '$':
        char cmd;
        cmd = serial_get();
        int value;
        value = serial_get() - 48;
        value *= 10;
        value += serial_get() - 48;

        Serial.print("cmd: ");
        Serial.print(cmd);
        Serial.print(" value: ");
        Serial.println(value);

        //setDS3231time(30,22,15,7,11,3,17);
        now = getTime();
        switch (cmd) {
          case 'Y':
          case 'y':
            setDS3231time(now.second, now.minute, now.hour, now.dayOfWeek, now.day, now.month, value);
            break;
          case 'N':
          case 'n':
            setDS3231time(now.second, now.minute, now.hour, now.dayOfWeek, now.day, value, now.year);
            break;
          case 'D':
          case 'd':
            setDS3231time(now.second, now.minute, now.hour, now.dayOfWeek, value, now.month, now.year);
            break;
          case 'H':
          case 'h':
            setDS3231time(now.second, now.minute, value, now.dayOfWeek, now.day, now.month, now.year);
            break;
          case 'M':
          case 'm':
            setDS3231time(now.second, value, now.hour, now.dayOfWeek, now.day, now.month, now.year);
            break;
          case 'S':
          case 's':
            setDS3231time(value, now.minute, now.hour, now.dayOfWeek, now.day, now.month, now.year);
            break;
          case '?':
            break;
          default:
            Serial.print(F("bad cmd: "));
            Serial.println(cmd);
            break;
        }

        Serial.println(getTime().toString());
        break;
        
      case 0x01:
        byte address;
        address = serial_get();
        byte data;
        data = serial_get();
        output_all(address, data);
        if (debug_mode) {
          Serial.print(address);
          Serial.print(' ');
          Serial.println(data);
        }
        /*
        byte data = serial_get();
        output_all(address, data);
        output_all(serial_get(), serial_get());
        */
        Serial.println(F("READY"));
        break;
      case 0x02:
        op_0x02();
        Serial.println(F("READY"));
        break;
      case 0x03:
        op_0x03();
        Serial.println(F("READY"));
        break;
      case 0x04:
        op_0x04();
        Serial.println(F("READY"));
        break;
      case 0xFF:
        debug_mode = serial_get();
        Serial.println(debug_mode);
        Serial.println(F("READY"));
        break;
      default:
        Serial.print(F("BAD OP CODE "));
        Serial.println(op_code);
    }
    
  }
  
}

void op_0x04() {
  const size_t buffer_size = 8 * MAX7219_COUNT;
  byte buffer[buffer_size];

  int idx = 0;
  while (idx < buffer_size) {
    byte value = serial_get();
    byte count = serial_get();
    for (int i=0; i<count; i++) {
      //please do no evil
      buffer[idx++] = value;
    }
  }
  /*
  for (int i=0; i<buffer_size; i++) {
    buffer[i] = serial_get();
  }
  */
  
  if (debug_mode) {
    for (int i=0; i<buffer_size; i++) {
      if (i > 0) {
        Serial.print(' ');
      }
      Serial.print(buffer[i]);
    }
    Serial.println();
  }

  for (byte row = 0; row < 8; row++) {
    digitalWrite(MAX7219_CS, LOW);
    for (int i=0; i<MAX7219_COUNT; i++) {
      shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, 0x01 + row);
      shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, buffer[i + row * MAX7219_COUNT]);
    }
    digitalWrite(MAX7219_CS, HIGH);
  }
  
}

void op_0x03() {
  const size_t buffer_size = 8 * MAX7219_COUNT;
  byte buffer[buffer_size];
  for (int i=0; i<buffer_size; i++) {
    buffer[i] = serial_get();
  }
  if (debug_mode) {
    for (int i=0; i<buffer_size; i++) {
      if (i > 0) {
        Serial.print(' ');
      }
      Serial.print(buffer[i]);
    }
    Serial.println();
  }

  for (byte row = 0; row < 8; row++) {
    digitalWrite(MAX7219_CS, LOW);
    for (int i=0; i<MAX7219_COUNT; i++) {
      shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, 0x01 + row);
      shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, buffer[i + row * MAX7219_COUNT]);
    }
    digitalWrite(MAX7219_CS, HIGH);
  }
  
}

void op_0x02() {
  const size_t buffer_size = 2 * MAX7219_COUNT;
  byte buffer[buffer_size];
  for (int i=0; i<buffer_size; i++) {
    buffer[i] = serial_get();
  }

  digitalWrite(MAX7219_CS, LOW);
  for (int i=0; i<buffer_size; i++) {
    shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, buffer[i]);
  }
  digitalWrite(MAX7219_CS, HIGH);

  if (debug_mode) {
    for (int i=0; i<buffer_size; i++) {
      if (i > 0) {
        Serial.print(' ');
      }
      Serial.print(buffer[i]);
    }
    Serial.println();
    
  }
}

void output_all(byte address, byte data)
{
  digitalWrite(MAX7219_CS, LOW);
  for (int i=0; i<MAX7219_COUNT; i++) {
    shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, address);
    shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, data);
  }
  digitalWrite(MAX7219_CS, HIGH);
}


void output(byte address, byte data)
{
  digitalWrite(MAX7219_CS, LOW);
  shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, address);
  shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, data);
  digitalWrite(MAX7219_CS, HIGH);
}

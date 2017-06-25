#define MAX7219_CLK 4
#define MAX7219_CS 5
#define MAX7219_DIN 6

#define MAX7219_COUNT 12

void initialise()
{
  digitalWrite(MAX7219_CS, HIGH);
  pinMode(MAX7219_DIN, OUTPUT);
  pinMode(MAX7219_CS, OUTPUT);
  pinMode(MAX7219_CLK, OUTPUT);
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println(F(__DATE__));
  Serial.println(F(__TIME__));

  initialise();
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
  Serial.println(F("READY"));
}

byte serial_get() {
  while (Serial.available() == 0) {
    delay(1);
  }
  return Serial.read();
}

byte debug_mode = false;

void loop() {
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
   * Debug Mode
   * 0xFF 0x01
   */
  while (Serial.available() > 0) {
    byte op_code = Serial.read();
    switch (op_code) {
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

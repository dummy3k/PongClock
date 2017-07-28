import serial, sys, os
import struct
import numpy as np
from arduino import MAX7219_COUNT, wait_ready
from benchmark import benchmark
from helper import logging_config

import logging
logger = logging.getLogger(__name__)

digits = [
    [
        [1,1,1],
        [1,0,1],
        [1,0,1],
        [1,0,1],
        [1,1,1],
    ],
    [
        [0,0,1],
        [0,0,1],
        [0,0,1],
        [0,0,1],
        [0,0,1],
    ],
    [
        [1,1,1],
        [0,0,1],
        [1,1,1],
        [1,0,0],
        [1,1,1],
    ],
    [
        [1,1,1],
        [0,0,1],
        [1,1,1],
        [0,0,1],
        [1,1,1],
    ],
    [
        [1,0,1],
        [1,0,1],
        [1,1,1],
        [0,0,1],
        [0,0,1],
    ],
    [
        [1,1,1],
        [1,0,0],
        [1,1,1],
        [0,0,1],
        [1,1,1],
    ],
    [
        [1,1,1],
        [1,0,0],
        [1,1,1],
        [1,0,1],
        [1,1,1],
    ],
    [
        [1,1,1],
        [0,0,1],
        [0,0,1],
        [0,0,1],
        [0,0,1],
    ],
    [
        [1,1,1],
        [1,0,1],
        [1,1,1],
        [1,0,1],
        [1,1,1],
    ],
    [
        [1,1,1],
        [1,0,1],
        [1,1,1],
        [0,0,1],
        [1,1,1],
    ],
]
        
class Bitmap():
    def __init__(self):
        self.stream = np.full((8, MAX7219_COUNT), 0)
        
    def setPixel(self, source_x, source_y):
        if source_y >= 16:
            x = 0
        elif source_y >= 8:
            x = 4
        else:
            x = 8
            
        x = x + source_x / 8
        y = source_y % 8
        v = 1 << 7 - source_x % 8

        self.stream[y][x] = self.stream[y][x] | v
        
    def arduino(self, com):
        self.arduino_0x04(com)
        
    def arduino_0x02(self, com):
        for r in range(8):
            com.write(struct.pack('B', 0x02))
            for v in self.stream[r]:
                com.write(struct.pack('BB', 0x01 + r, v))
            wait_ready(com)
        
    def arduino_0x03(self, com):
        com.write(struct.pack('B', 0x03))
        for r in range(8):
            for v in self.stream[r]:
                com.write(struct.pack('B', v))
        wait_ready(com)
        
    def arduino_0x04(self, com):
        data = []
        for r in range(8):
            data = data + self.stream[r].tolist()
        # print(data)
        data = rle_encode(data)
        logger.debug("data.len: %s" % len(data))

        com.write(struct.pack('B', 0x04))
        for item in data:
            com.write(struct.pack('B', item))
        
        wait_ready(com)
        
    def render_digit(self, digit, offset):
        for i, row in enumerate(digits[digit]):
            for j, col in enumerate(row):
                if col:
                    self.setPixel(offset[0] + j, offset[1] + i)
                    
        
def paddle(com):
    while True:
        for y in range(16):
            bmp = Bitmap()
            for n in range(8):
                bmp.setPixel(1, y + n)
                bmp.setPixel(30, 31 - 8 - (y + n))
                
            bmp.arduino(com)
        for y in range(16, 0, -1):
            bmp = Bitmap()
            for n in range(8):
                bmp.setPixel(1, y + n)
                bmp.setPixel(30, 31 - 8 - (y + n))
            bmp.arduino(com)

#0 0 0 0 64 0 0 0 0 0 0 0 0 0 0 0 64 0 0 0 0 0 0 0 0 0 0 0 64 0 0 0 0 0 0 0 0 0 0 0 64 0 0 0 0 0 0 0 0 0 0 0 64 0 0 0 0 0 0 0 0 0 0 0 64 0 0 0 0 0 0 0 0 0 0 0 64 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 64 0 0 0
#0 4 64 1 0 11 64 1 0 11 64 1 0 11 64 1 0 11
def rle_encode(data):
    """
        >>> rle_encode([0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
        [0, 4, 64, 1, 0, 11]
        
        >>> rle_encode([0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0])
        [0, 4, 64, 1, 0, 11, 64, 1, 0, 11, 64, 1, 0, 11, 64, 1, 0, 11, 64, 1, 0, 11, 64, 1, 0, 11, 64, 1, 0, 15, 64, 1, 0, 3]
        
    """
    # return "x"
    retVal = [data[0]]
    count = 1
    for item in data[1:]:
        # print(item)
        if item == retVal[-1]:
            count = count + 1
        else:
            retVal.append(count)
            count = 1
            retVal.append(item)
            
    retVal.append(count)
    return retVal
        
def benchmark_1px(com):
    bmp = Bitmap()
    bmp.setPixel(1, 1)
    with benchmark("arduino_0x02") as b2:
        bmp.arduino_0x02(com)
    with benchmark("arduino_0x03") as b3:
        bmp.arduino_0x03(com)
    with benchmark("arduino_0x04") as b4:
        bmp.arduino_0x04(com)
        
    print(b2.time)
    print(b3.time)
    print(b4.time)

if __name__ == '__main__':                
    # print(rle_encode([0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]))
    logging_config()
    import logging.config
    logging.config.dictConfig({ 
        'version': 1,
        'incremental':True,
        'disable_existing_loggers': False,
        'loggers': { 
            '': { 
                'handlers': ['default'],
                'level': 'DEBUG',
                'propagate': True
            },
            'arduino': { 
                'handlers': ['default'],
                'level': 'WARN',
                'propagate': False
            },
        } 
    })
    
    logger.debug("DEBUG")
    logger.info("INFO")
    
    with serial.Serial("COM5") as com:
        com.timeout = 3
        wait_ready(com)

        # com.write(struct.pack('BB', 0xFF, 0x01))  #debug mode
        # wait_ready(com)
        
        com.write(struct.pack('BBB', 0x01, 0x0a, 0x01))  #brightness
        wait_ready(com)
        
        # benchmark_1px(com)
        paddle(com)
        
        
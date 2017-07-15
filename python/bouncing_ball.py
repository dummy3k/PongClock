import serial, sys, os, time, datetime
import struct
import numpy as np
from arduino import MAX7219_COUNT, wait_ready
from benchmark import benchmark
from helper import logging_config
from rle import Bitmap
import random
import logging
logger = logging.getLogger(__name__)

if __name__ == '__main__':                
    # print(rle_encode([0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]))
    logging_config()

    now = datetime.datetime.now()
    
    scoreLeft = now.hour
    scoreRight = now.minute

    start_pos = (12, 12)
    impulse = np.array((1, 3))
    impulse = np.array((random.random(), random.random()))
    impulse = impulse/np.linalg.norm(impulse)
    # impulse = impulse/10
    
    paddle_left_pos = 12
    paddle_right_pos = 12
        
    with serial.Serial("COM5") as com:
        com.timeout = 3
        wait_ready(com)

        com.write(struct.pack('BBB', 0x01, 0x0a, 0x01))  #brightness
        wait_ready(com)
        
        t = 0
        last_pos = None
        while True:
            pos_t = impulse * t
            pos_t = map(lambda x: int(round(x)), pos_t)
            
            pos_t[0] = pos_t[0] + start_pos[0]
            pos_t[1] = pos_t[1] + start_pos[1]

            if (pos_t[1] < 0 or pos_t[1] >= 24):
                impulse[1] = impulse[1] * -1
                start_pos = last_pos
                t = 1
                continue
            elif (pos_t[0] == 1 or pos_t[0] == 2) and pos_t[1] >= paddle_left_pos - 2 and pos_t[1] <= paddle_left_pos + 2:
                impulse[0] = impulse[0] * -1
                impulse[1] += (pos_t[1] - paddle_left_pos) * 0.5
                impulse = impulse/np.linalg.norm(impulse)
                start_pos = last_pos
                t = 1
            
            elif (pos_t[0] == 29 or pos_t[0] == 30) and pos_t[1] >= paddle_right_pos - 2 and pos_t[1] <= paddle_right_pos + 2:
                impulse[0] = impulse[0] * -1
                impulse[1] += (pos_t[1] - paddle_left_pos) * 0.01
                impulse = impulse/np.linalg.norm(impulse)
                start_pos = last_pos
                t = 1            
            
            elif (pos_t[0] < 0 or pos_t[0] >= 32):
                now = datetime.datetime.now()
                scoreLeft = now.hour
                scoreRight = now.minute
                
                # impulse[0] = impulse[0] * -1
                impulse = np.array((random.random(), random.random()))
                impulse = impulse/np.linalg.norm(impulse)
                
                start_pos = (12, 12)
                paddle_left_pos = 12
                paddle_right_pos = 12
                t = 1
                continue
            
            logger.debug("i: %s %s" % (impulse, pos_t))
            bmp = Bitmap()
            bmp.setPixel(*pos_t)
            
            now = datetime.datetime.now()
            
            if scoreLeft != now.hour:
                f1 = 0.9
            else:
                f1 = 0.0
            if scoreRight != now.minute:
                f2 = 0.9
            else:
                f2 = 0.0
        
            if random.random() > f1 and impulse[0] > 0:
                delta = paddle_right_pos - pos_t[1]
                if delta > 0:
                    paddle_right_pos = paddle_right_pos - 1
                elif delta < 0:
                    paddle_right_pos = paddle_right_pos + 1
                    
                # paddle_right_pos = pos_t[1]
                paddle_right_pos = min(paddle_right_pos, 21)
                paddle_right_pos = max(paddle_right_pos, 2)
            elif random.random() > f2 and impulse[0] <= 0:
                delta = paddle_left_pos - pos_t[1]
                if delta > 0:
                    paddle_left_pos = paddle_left_pos - 1
                elif delta < 0:
                    paddle_left_pos = paddle_left_pos + 1
                # paddle_left_pos = pos_t[1]
                paddle_left_pos = min(paddle_left_pos, 21)
                paddle_left_pos = max(paddle_left_pos, 2)
            
            for y in range(paddle_left_pos - 2, paddle_left_pos + 3):
                bmp.setPixel(1, y)
                
            for y in range(paddle_right_pos - 2, paddle_right_pos + 3):
                bmp.setPixel(30, y)
            
            hour1 = scoreLeft / 10
            bmp.render_digit(hour1, (8,18))
            hour2 = scoreLeft % 10
            bmp.render_digit(hour2, (12,18))
            minute1 = scoreRight / 10
            bmp.render_digit(minute1, (17,18))
            minute2 = scoreRight % 10
            bmp.render_digit(minute2, (21,18))
            
            bmp.arduino(com)
            # time.sleep(1)
            last_pos = pos_t
            t = t + 1
            

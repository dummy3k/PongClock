import png
import serial, sys, os, struct
import numpy as np
from arduino import wait_ready


def display():
    with open('rect.png', 'rb') as f:
        img = png.Reader(file=f)
        #print(img.read())
        width, height, pixels, options = img.read()
        if width != 32 or height != 8:
            raise Exception("bad size")
            
        with serial.Serial("COM5") as com:
            com.timeout = 3
            wait_ready(com)

            for row, line_pixels in enumerate(pixels):
                print(line_pixels)
                tmp = 0
                for col, pixel in enumerate(line_pixels):
                    tmp = tmp << 1
                    tmp = tmp | pixel
                    
                    if col % 8 == 7:
                        print(tmp)
                        com.write(struct.pack('BB', 0x01 + row, tmp))
                        tmp = 0
                        # wait_ready(com)
                        # os.system("pause")
                        
                wait_ready(com)
                # if not os.system("pause"):
                    # raise Exception("get me out of here")
                

def blank(com):
    #output_all(0x0a, 0x0f); //
    
    for r in range(8):
        for n in range(MAX7219_COUNT):
            if r == 0 and n == 0:
                com.write(struct.pack('BB', 0x01 + r, 1))
            else:
                com.write(struct.pack('BB', 0x01 + r, 0))
    
        wait_ready(com)


        
def draw(com):
    for source_y in range(24):
        for source_x in range(32):
            if source_y >= 16:
                x = 0
            elif source_y >= 8:
                x = 4
            else:
                x = 8
                
            x = x + source_x / 8
            y = source_y % 8
            v = 1 << 7 - source_x % 8

            stream = np.full((8, MAX7219_COUNT), 0)
            stream[y][x] = v
                
            for r in range(8):
                for v in stream[r]:
                    com.write(struct.pack('BB', 0x01 + r, v))
                wait_ready(com)

if __name__ == '__main__':                
    with serial.Serial("COM5") as com:
        com.timeout = 3
        wait_ready(com)

        for n in range(MAX7219_COUNT):
            com.write(struct.pack('BB', 0x0A, 0x00))   #intensity register - max brightness
        wait_ready(com)

        draw(com)
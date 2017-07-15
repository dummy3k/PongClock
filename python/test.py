import serial, sys, os
import struct
from tabulate import tabulate


        
    # print("'%s'" % last_line)
    
def write_to_arduino(msg):
    with serial.Serial("COM5", 9600) as com:
        # com.timeout = 3
        wait_ready(com)
        
            
        # print(com.read_all())
        com.write(msg)
        wait_ready(com)

        

def update_register(addr, value):
    for n in range(4):
        com.write(struct.pack('BB', addr, value))
    wait_ready(com)

if __name__ == '__main__':    
    with serial.Serial("COM5") as com:
        com.timeout = 3
        wait_ready(com)
        
        
        # update_register(0x01, 0x01)
        #update_register(0x03, 0x07)
        
        update_register(0x01, 0xFF)
        update_register(0x08, 0xFF)
        
        # for x in range(8):
            # for y in range(8):
                # update_register(0x01 + y, 0x00 + x)
            # os.system("pause")
            
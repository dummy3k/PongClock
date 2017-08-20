EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:PongClock
LIBS:switches
LIBS:PongClock-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MAX7219_IN U2
U 1 1 596A2A6D
P 7350 4250
F 0 "U2" H 8200 3900 60  0000 C CNN
F 1 "MAX7219_IN" H 7800 3900 60  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x05_Pitch2.54mm" H 7350 4250 60  0001 C CNN
F 3 "" H 7350 4250 60  0001 C CNN
	1    7350 4250
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR14
U 1 1 596A2EB4
P 6800 4400
F 0 "#PWR14" H 6800 4250 50  0001 C CNN
F 1 "VCC" V 6800 4600 50  0000 C CNN
F 2 "" H 6800 4400 50  0001 C CNN
F 3 "" H 6800 4400 50  0001 C CNN
	1    6800 4400
	0    -1   -1   0   
$EndComp
NoConn ~ 6800 4600
$Comp
L MAX7219_IN U3
U 1 1 597B8DED
P 7350 4850
F 0 "U3" H 8200 4500 60  0000 C CNN
F 1 "MAX7219_IN" H 7800 4500 60  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x05_Pitch2.54mm" H 7350 4850 60  0001 C CNN
F 3 "" H 7350 4850 60  0001 C CNN
	1    7350 4850
	1    0    0    -1  
$EndComp
NoConn ~ 6800 5200
$Comp
L MAX7219_IN U4
U 1 1 597B8E78
P 7350 5450
F 0 "U4" H 8200 5100 60  0000 C CNN
F 1 "MAX7219_IN" H 7800 5100 60  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x05_Pitch2.54mm" H 7350 5450 60  0001 C CNN
F 3 "" H 7350 5450 60  0001 C CNN
	1    7350 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR23
U 1 1 597B8E84
P 6800 5700
F 0 "#PWR23" H 6800 5450 50  0001 C CNN
F 1 "GND" V 6800 5500 50  0000 C CNN
F 2 "" H 6800 5700 50  0001 C CNN
F 3 "" H 6800 5700 50  0001 C CNN
	1    6800 5700
	0    1    1    0   
$EndComp
NoConn ~ 6800 5800
$Comp
L MAX7219_IN U5
U 1 1 597B8E8D
P 9600 4250
F 0 "U5" H 10450 3900 60  0000 C CNN
F 1 "MAX7219_IN" H 10050 3900 60  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x05_Pitch2.54mm" H 9600 4250 60  0001 C CNN
F 3 "" H 9600 4250 60  0001 C CNN
	1    9600 4250
	1    0    0    -1  
$EndComp
Text GLabel 9050 4700 0    60   Input ~ 0
LATCH
Text GLabel 9050 4800 0    60   Input ~ 0
CLK
NoConn ~ 9050 4600
$Comp
L CONN_01X01_MALE J1
U 1 1 597B8EB0
P 8450 4050
F 0 "J1" H 8450 4125 50  0000 C CNN
F 1 "CONN_01X01_MALE" H 8450 3950 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_1x01_Pitch2.54mm" H 8450 4050 50  0001 C CNN
F 3 "" H 8450 4050 50  0001 C CNN
	1    8450 4050
	-1   0    0    1   
$EndComp
Text GLabel 8150 4050 0    60   Input ~ 0
MAX_IN
$Comp
L MAX7219_IN U6
U 1 1 597C60B3
P 9600 4850
F 0 "U6" H 10450 4500 60  0000 C CNN
F 1 "MAX7219_IN" H 10050 4500 60  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x05_Pitch2.54mm" H 9600 4850 60  0001 C CNN
F 3 "" H 9600 4850 60  0001 C CNN
	1    9600 4850
	1    0    0    -1  
$EndComp
Text GLabel 9050 5300 0    60   Input ~ 0
LATCH
Text GLabel 9050 5400 0    60   Input ~ 0
CLK
NoConn ~ 9050 5200
$Comp
L MAX7219_IN U7
U 1 1 597C60C8
P 9600 5450
F 0 "U7" H 10450 5100 60  0000 C CNN
F 1 "MAX7219_IN" H 10050 5100 60  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x05_Pitch2.54mm" H 9600 5450 60  0001 C CNN
F 3 "" H 9600 5450 60  0001 C CNN
	1    9600 5450
	1    0    0    -1  
$EndComp
NoConn ~ 9050 5800
NoConn ~ 9050 4400
NoConn ~ 9050 5000
NoConn ~ 6800 5300
NoConn ~ 6800 5400
NoConn ~ 6800 4700
NoConn ~ 6800 4800
$Comp
L VCC #PWR18
U 1 1 597C7538
P 6800 5000
F 0 "#PWR18" H 6800 4850 50  0001 C CNN
F 1 "VCC" V 6800 5200 50  0000 C CNN
F 2 "" H 6800 5000 50  0001 C CNN
F 3 "" H 6800 5000 50  0001 C CNN
	1    6800 5000
	0    -1   -1   0   
$EndComp
$Comp
L ATMEGA328P-PU U8
U 1 1 598DF1B2
P 1950 2150
F 0 "U8" H 1200 3400 50  0000 L BNN
F 1 "ATMEGA328P-PU" H 2350 750 50  0000 L BNN
F 2 "Housings_DIP:DIP-28_W7.62mm_Socket_LongPads" H 1950 2150 50  0001 C CIN
F 3 "" H 1950 2150 50  0001 C CNN
	1    1950 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 598DFC0D
P 1050 3300
F 0 "#PWR8" H 1050 3050 50  0001 C CNN
F 1 "GND" V 1050 3100 50  0000 C CNN
F 2 "" H 1050 3300 50  0001 C CNN
F 3 "" H 1050 3300 50  0001 C CNN
	1    1050 3300
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR1
U 1 1 598DFC7E
P 1050 1350
F 0 "#PWR1" H 1050 1200 50  0001 C CNN
F 1 "VCC" V 1050 1550 50  0000 C CNN
F 2 "" H 1050 1350 50  0001 C CNN
F 3 "" H 1050 1350 50  0001 C CNN
	1    1050 1350
	0    -1   -1   0   
$EndComp
Text GLabel 2950 1650 2    60   Input ~ 0
OSC1
Text GLabel 2950 1750 2    60   Input ~ 0
OSC2
Text GLabel 4800 1750 3    60   Input ~ 0
OSC2
Text GLabel 4800 1250 1    60   Input ~ 0
OSC1
$Comp
L GND #PWR3
U 1 1 598E0208
P 4300 1500
F 0 "#PWR3" H 4300 1250 50  0001 C CNN
F 1 "GND" V 4300 1300 50  0000 C CNN
F 2 "" H 4300 1500 50  0001 C CNN
F 3 "" H 4300 1500 50  0001 C CNN
	1    4300 1500
	0    1    1    0   
$EndComp
Connection ~ 1050 1350
Wire Wire Line
	1050 3250 1050 3350
Connection ~ 1050 3300
$Comp
L C C1
U 1 1 598E090A
P 4450 1350
F 0 "C1" H 4475 1450 50  0000 L CNN
F 1 "22pF" V 4300 1300 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 4488 1200 50  0001 C CNN
F 3 "" H 4450 1350 50  0001 C CNN
	1    4450 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 1250 4800 1350
Wire Wire Line
	4800 1350 4600 1350
Wire Wire Line
	4300 1350 4300 1650
$Comp
L C C2
U 1 1 598E0A25
P 4450 1650
F 0 "C2" H 4475 1750 50  0000 L CNN
F 1 "22pF" V 4650 1600 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 4488 1500 50  0001 C CNN
F 3 "" H 4450 1650 50  0001 C CNN
	1    4450 1650
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 1750 4800 1650
Wire Wire Line
	4800 1650 4600 1650
Connection ~ 4300 1500
$Comp
L FTDI1232 U9
U 1 1 598E1785
P 4400 2500
F 0 "U9" H 4850 1750 60  0000 C CNN
F 1 "FTDI1232" H 4500 1750 60  0000 C CNN
F 2 "Connectors:PINHEAD1-6" H 4400 2500 60  0001 C CNN
F 3 "" H 4400 2500 60  0001 C CNN
	1    4400 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR7
U 1 1 598E32E5
P 4150 3050
F 0 "#PWR7" H 4150 2800 50  0001 C CNN
F 1 "GND" V 4150 2850 50  0000 C CNN
F 2 "" H 4150 3050 50  0001 C CNN
F 3 "" H 4150 3050 50  0001 C CNN
	1    4150 3050
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR6
U 1 1 598E33DE
P 4150 2750
F 0 "#PWR6" H 4150 2600 50  0001 C CNN
F 1 "VCC" V 4150 2950 50  0000 C CNN
F 2 "" H 4150 2750 50  0001 C CNN
F 3 "" H 4150 2750 50  0001 C CNN
	1    4150 2750
	0    -1   -1   0   
$EndComp
Text GLabel 2950 2650 2    60   Input ~ 0
RX
Text GLabel 2950 2750 2    60   Input ~ 0
TX
Text GLabel 5000 2850 2    60   Input ~ 0
RX
Text GLabel 5000 2750 2    60   Input ~ 0
TX
$Comp
L C C3
U 1 1 598E395B
P 5700 2950
F 0 "C3" H 5725 3050 50  0000 L CNN
F 1 "10uF" V 5850 2850 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 5738 2800 50  0001 C CNN
F 3 "" H 5700 2950 50  0001 C CNN
	1    5700 2950
	0    1    1    0   
$EndComp
Text GLabel 6000 2950 2    60   Input ~ 0
RESET
Text GLabel 2950 2500 2    60   Input ~ 0
RESET
Text GLabel 2950 3350 2    60   Input ~ 0
MAX_IN
Text GLabel 2950 3150 2    60   Input ~ 0
LATCH
Text GLabel 2950 3250 2    60   Input ~ 0
CLK
Text GLabel 2950 2300 2    60   Input ~ 0
SDA
Text GLabel 2950 2400 2    60   Input ~ 0
SCL
Text GLabel 2950 2950 2    60   Input ~ 0
SW1
Text GLabel 2950 3050 2    60   Input ~ 0
SW2
$Comp
L GND #PWR16
U 1 1 598EBAEB
P 4250 4600
F 0 "#PWR16" H 4250 4350 50  0001 C CNN
F 1 "GND" V 4250 4400 50  0000 C CNN
F 2 "" H 4250 4600 50  0001 C CNN
F 3 "" H 4250 4600 50  0001 C CNN
	1    4250 4600
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR9
U 1 1 598EBB74
P 4550 4000
F 0 "#PWR9" H 4550 3850 50  0001 C CNN
F 1 "VCC" V 4550 4200 50  0000 C CNN
F 2 "" H 4550 4000 50  0001 C CNN
F 3 "" H 4550 4000 50  0001 C CNN
	1    4550 4000
	0    1    1    0   
$EndComp
NoConn ~ 4550 4200
NoConn ~ 4550 4300
NoConn ~ 4550 4400
NoConn ~ 4150 4600
NoConn ~ 5000 3050
$Comp
L MY_USB_OTG J2
U 1 1 598EE15E
P 4250 4200
F 0 "J2" H 4050 4650 50  0000 L CNN
F 1 "MY_USB_OTG" H 4050 4550 50  0000 L CNN
F 2 "PongClock:USB_BOARD" H 4400 4150 50  0001 C CNN
F 3 "" H 4400 4150 50  0001 C CNN
	1    4250 4200
	1    0    0    -1  
$EndComp
NoConn ~ 2950 1050
NoConn ~ 2950 1150
NoConn ~ 2950 1250
NoConn ~ 2950 1350
NoConn ~ 2950 1450
NoConn ~ 2950 1550
NoConn ~ 2950 1900
NoConn ~ 2950 2000
NoConn ~ 2950 2100
Wire Wire Line
	1050 1050 1050 1350
NoConn ~ 1050 1650
Text GLabel 2950 2850 2    60   Input ~ 0
LED
Text GLabel 1150 4950 0    60   Input ~ 0
LED
$Comp
L R R3
U 1 1 598EFE16
P 1300 4950
F 0 "R3" V 1380 4950 50  0000 C CNN
F 1 "R_LED" V 1200 4950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1230 4950 50  0001 C CNN
F 3 "" H 1300 4950 50  0001 C CNN
	1    1300 4950
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 598F0345
P 1600 4950
F 0 "D1" H 1600 5050 50  0000 C CNN
F 1 "LED" H 1600 4850 50  0000 C CNN
F 2 "LEDs:LED_1206_HandSoldering" H 1600 4950 50  0001 C CNN
F 3 "" H 1600 4950 50  0001 C CNN
	1    1600 4950
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR17
U 1 1 598F03E6
P 1750 4950
F 0 "#PWR17" H 1750 4700 50  0001 C CNN
F 1 "GND" V 1750 4750 50  0000 C CNN
F 2 "" H 1750 4950 50  0001 C CNN
F 3 "" H 1750 4950 50  0001 C CNN
	1    1750 4950
	0    -1   -1   0   
$EndComp
$Comp
L TinyRTC_I2C_RIGHT U1
U 1 1 598F1A94
P 5950 1500
F 0 "U1" H 5950 1100 60  0000 C CNN
F 1 "TinyRTC_I2C_RIGHT" H 5950 1200 60  0000 C CNN
F 2 "PongClock:TINY_RTC_RIGHT" H 5700 1850 60  0001 C CNN
F 3 "" H 5700 1850 60  0001 C CNN
	1    5950 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR4
U 1 1 598F1B59
P 5650 1650
F 0 "#PWR4" H 5650 1400 50  0001 C CNN
F 1 "GND" V 5650 1450 50  0000 C CNN
F 2 "" H 5650 1650 50  0001 C CNN
F 3 "" H 5650 1650 50  0001 C CNN
	1    5650 1650
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR2
U 1 1 598F1BAC
P 5650 1350
F 0 "#PWR2" H 5650 1200 50  0001 C CNN
F 1 "VCC" V 5650 1550 50  0000 C CNN
F 2 "" H 5650 1350 50  0001 C CNN
F 3 "" H 5650 1350 50  0001 C CNN
	1    5650 1350
	0    -1   -1   0   
$EndComp
Text GLabel 6250 1650 2    60   Input ~ 0
SDA
Text GLabel 6250 1550 2    60   Input ~ 0
SCL
NoConn ~ 6250 1450
NoConn ~ 6250 1350
$Comp
L Crystal Y1
U 1 1 598F2D1C
P 4800 1500
F 0 "Y1" H 4800 1650 50  0000 C CNN
F 1 "Crystal" H 4800 1350 50  0000 C CNN
F 2 "Crystals:Resonator_SMD_muRata_CDSCB-2pin_4.5x2.0mm_HandSoldering" H 4800 1500 50  0001 C CNN
F 3 "" H 4800 1500 50  0001 C CNN
	1    4800 1500
	0    1    1    0   
$EndComp
$Comp
L C C4
U 1 1 598F6208
P 1600 4050
F 0 "C4" H 1625 4150 50  0000 L CNN
F 1 "100nF" V 1450 3900 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 1638 3900 50  0001 C CNN
F 3 "" H 1600 4050 50  0001 C CNN
	1    1600 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	1900 4350 1900 4050
Wire Wire Line
	1900 4050 1750 4050
Wire Wire Line
	1300 4350 1300 4050
Wire Wire Line
	1300 4050 1450 4050
$Comp
L R R1
U 1 1 598F638D
P 1150 4250
F 0 "R1" V 1230 4250 50  0000 C CNN
F 1 "10k" V 1150 4250 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 1080 4250 50  0001 C CNN
F 3 "" H 1150 4250 50  0001 C CNN
	1    1150 4250
	0    1    1    0   
$EndComp
$Comp
L GND #PWR12
U 1 1 598F641F
P 1000 4250
F 0 "#PWR12" H 1000 4000 50  0001 C CNN
F 1 "GND" V 1000 4050 50  0000 C CNN
F 2 "" H 1000 4250 50  0001 C CNN
F 3 "" H 1000 4250 50  0001 C CNN
	1    1000 4250
	0    1    1    0   
$EndComp
Text GLabel 1300 4100 0    60   Input ~ 0
SW1
$Comp
L VCC #PWR10
U 1 1 598F657A
P 1900 4200
F 0 "#PWR10" H 1900 4050 50  0001 C CNN
F 1 "VCC" V 1900 4400 50  0000 C CNN
F 2 "" H 1900 4200 50  0001 C CNN
F 3 "" H 1900 4200 50  0001 C CNN
	1    1900 4200
	0    1    1    0   
$EndComp
$Comp
L C C5
U 1 1 598F6A52
P 2800 4050
F 0 "C5" H 2825 4150 50  0000 L CNN
F 1 "100nF" V 2650 4000 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 2838 3900 50  0001 C CNN
F 3 "" H 2800 4050 50  0001 C CNN
	1    2800 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	3100 4350 3100 4050
Wire Wire Line
	3100 4050 2950 4050
Wire Wire Line
	2500 4350 2500 4050
Wire Wire Line
	2500 4050 2650 4050
$Comp
L R R2
U 1 1 598F6A5C
P 3250 4300
F 0 "R2" V 3330 4300 50  0000 C CNN
F 1 "10k" V 3250 4300 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 3180 4300 50  0001 C CNN
F 3 "" H 3250 4300 50  0001 C CNN
	1    3250 4300
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR13
U 1 1 598F6A62
P 3400 4300
F 0 "#PWR13" H 3400 4050 50  0001 C CNN
F 1 "GND" V 3400 4100 50  0000 C CNN
F 2 "" H 3400 4300 50  0001 C CNN
F 3 "" H 3400 4300 50  0001 C CNN
	1    3400 4300
	0    -1   -1   0   
$EndComp
Text GLabel 3100 4100 2    60   Input ~ 0
SW2
$Comp
L VCC #PWR11
U 1 1 598F6A69
P 2500 4200
F 0 "#PWR11" H 2500 4050 50  0001 C CNN
F 1 "VCC" V 2500 4400 50  0000 C CNN
F 2 "" H 2500 4200 50  0001 C CNN
F 3 "" H 2500 4200 50  0001 C CNN
	1    2500 4200
	0    -1   -1   0   
$EndComp
Connection ~ 3100 4300
Connection ~ 3100 4100
Connection ~ 2500 4200
Connection ~ 1300 4100
Connection ~ 1300 4250
Connection ~ 1900 4200
$Comp
L VCC #PWR22
U 1 1 598FAE5F
P 6800 5600
F 0 "#PWR22" H 6800 5450 50  0001 C CNN
F 1 "VCC" V 6800 5800 50  0000 C CNN
F 2 "" H 6800 5600 50  0001 C CNN
F 3 "" H 6800 5600 50  0001 C CNN
	1    6800 5600
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR5
U 1 1 598FC725
P 5900 2650
F 0 "#PWR5" H 5900 2500 50  0001 C CNN
F 1 "VCC" V 5900 2850 50  0000 C CNN
F 2 "" H 5900 2650 50  0001 C CNN
F 3 "" H 5900 2650 50  0001 C CNN
	1    5900 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 2950 6000 2950
Connection ~ 5900 2950
$Comp
L R R4
U 1 1 598FD057
P 5900 2800
F 0 "R4" V 5980 2800 50  0000 C CNN
F 1 "10k" V 5900 2800 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 5830 2800 50  0001 C CNN
F 3 "" H 5900 2800 50  0001 C CNN
	1    5900 2800
	1    0    0    -1  
$EndComp
NoConn ~ 9050 5700
$Comp
L SW_DIP_x01 SW1
U 1 1 59933064
P 1600 4350
F 0 "SW1" H 1600 4500 50  0000 C CNN
F 1 "SW_DIP_x01" H 1600 4200 50  0000 C CNN
F 2 "mod_switch:smd_push" H 1600 4350 50  0001 C CNN
F 3 "" H 1600 4350 50  0001 C CNN
	1    1600 4350
	1    0    0    -1  
$EndComp
$Comp
L SW_DIP_x01 SW2
U 1 1 599332E9
P 2800 4350
F 0 "SW2" H 2800 4500 50  0000 C CNN
F 1 "SW_DIP_x01" H 2800 4200 50  0000 C CNN
F 2 "mod_switch:smd_push" H 2800 4350 50  0001 C CNN
F 3 "" H 2800 4350 50  0001 C CNN
	1    2800 4350
	1    0    0    -1  
$EndComp
Text GLabel 5000 2950 2    60   Input ~ 0
DTR
Text GLabel 5550 2950 0    60   Input ~ 0
DTR
Text GLabel 9050 6000 0    60   Input ~ 0
CLK
Text GLabel 9050 5900 0    60   Input ~ 0
LATCH
$Comp
L GND #PWR19
U 1 1 59935016
P 6800 5100
F 0 "#PWR19" H 6800 4850 50  0001 C CNN
F 1 "GND" V 6800 4900 50  0000 C CNN
F 2 "" H 6800 5100 50  0001 C CNN
F 3 "" H 6800 5100 50  0001 C CNN
	1    6800 5100
	0    1    1    0   
$EndComp
$Comp
L GND #PWR15
U 1 1 59935069
P 6800 4500
F 0 "#PWR15" H 6800 4250 50  0001 C CNN
F 1 "GND" V 6800 4300 50  0000 C CNN
F 2 "" H 6800 4500 50  0001 C CNN
F 3 "" H 6800 4500 50  0001 C CNN
	1    6800 4500
	0    1    1    0   
$EndComp
NoConn ~ 9050 5600
NoConn ~ 9050 4500
NoConn ~ 9050 5100
NoConn ~ 6800 5900
NoConn ~ 6800 6000
$Comp
L R_PHOTO R6
U 1 1 5999D738
P 1900 5600
F 0 "R6" H 1950 5650 50  0000 L CNN
F 1 "R_PHOTO" H 1950 5600 50  0000 L TNN
F 2 "" V 1950 5350 50  0001 L CNN
F 3 "" H 1900 5550 50  0001 C CNN
	1    1900 5600
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR21
U 1 1 5999D7E2
P 2050 5600
F 0 "#PWR21" H 2050 5450 50  0001 C CNN
F 1 "VCC" V 2050 5800 50  0000 C CNN
F 2 "" H 2050 5600 50  0001 C CNN
F 3 "" H 2050 5600 50  0001 C CNN
	1    2050 5600
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 5999D838
P 1600 5600
F 0 "R5" V 1680 5600 50  0000 C CNN
F 1 "10k" V 1600 5600 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 1530 5600 50  0001 C CNN
F 3 "" H 1600 5600 50  0001 C CNN
	1    1600 5600
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR20
U 1 1 5999D8E6
P 1450 5600
F 0 "#PWR20" H 1450 5350 50  0001 C CNN
F 1 "GND" V 1450 5400 50  0000 C CNN
F 2 "" H 1450 5600 50  0001 C CNN
F 3 "" H 1450 5600 50  0001 C CNN
	1    1450 5600
	0    1    1    0   
$EndComp
Text GLabel 1750 5600 1    60   Input ~ 0
PHOTO
Text GLabel 2950 2200 2    60   Input ~ 0
PHOTO
$EndSCHEMATC

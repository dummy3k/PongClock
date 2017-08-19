(Block-name: Probe)
(Block-expand: 1)
(Block-enable: 1)

G38.2 Z-26 F10

G91
G00 Z1

(Block-name: Down)
(Block-expand: 1)
(Block-enable: 1)

M03 S15000 F90
G04 P2
G01 Z-1.1

(Block-name: X-Axis)
(Block-expand: 1)
(Block-enable: 1)

G01 X5
G01 Y-0.325
G01 X-5

(Block-name: X-Axis)
(Block-expand: 1)
(Block-enable: 1)
G00 Z1
M5
G00 Y-1

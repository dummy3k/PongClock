(Block-name: Probe)
(Block-expand: 1)
(Block-enable: 1)

G38.2 Z-26 F10

G91
G00 Z1

(Block-name: Down)
(Block-expand: 1)
(Block-enable: 1)

M03 S10000 F100
G01 Z-1.05

(Block-name: X-Axis)
(Block-expand: 1)
(Block-enable: 1)

G01 X10
G01 Y-0.363
G01 X-10

(Block-name: X-Axis)
(Block-expand: 1)
(Block-enable: 1)
G00 Z1
M5
G00 Y-1

; tpost1.g

;PCF fan on
M106 R2

;wait for heatup
M116 P1

G90
G1 U{global.xsize} F6000

G1 R2 Z0
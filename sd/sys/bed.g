M561                ; clear any existing bed transform

T0                  ;always probe with T0

G91
G1 Z5 F{global.speed_z}
G90

G30 P0 X20  Y32.5  Z-99999
G30 P1 X20  Y160   Z-99999
G30 P2 X20  Y287.5 Z-99999
G30 P3 X300 Y287.5 Z-99999
G30 P4 X300 Y160   Z-99999
G30 P5 X300 Y32.5  Z-99999 S3


;homez.g
G29 S2
T0              ;always home with T0

G91             ;relative mode
G1 Z5 F{global.speed_z} H2   ;lower the bed
G90             ;absolute mode

; use G53 below because it needs to be relative to the probe
G53 G1 X{global.xcenter} Y{global.ycenter} F{global.speed_xy} ;position probe above center

M558 F{global.speed_zhome_fast}
G30

M558 F{global.speed_zhome_slow}
G30

G29 S1
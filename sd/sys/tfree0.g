;tfree0.g
G91
G1 Z{global.zclearance} F{global.speed_z}
G90
G53 G1 X{global.t0park} F{global.speed_xy} ; park the tool
;fan off
M106 P1 S0

set global.cur_tool = "default"
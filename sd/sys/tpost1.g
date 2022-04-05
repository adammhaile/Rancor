; tpost1.g
;PCF fan on
M106 R2

M98 P"t1wipe.g"
	
G1 R2 Z0

set global.cur_tool = global.t1tool
M703

if {global.allow_filament_sensor}
    M591 D1 S1
else
    M591 D1 S0
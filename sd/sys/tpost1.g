; tpost1.g
;PCF fan on
M106 R2

;wait for heatup
M116 P1

M98 P"t1wipe.g"
	
G1 R2 Z0

set global.cur_tool = global.t1tool
M703
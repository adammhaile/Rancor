; tpost0.g
;PCF fan on
M106 R2

M98 P"t0wipe.g"
	
G1 R2 Z0

set global.cur_tool = global.t0tool
M703


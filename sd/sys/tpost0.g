; tpost0.g
;PCF fan on
M106 R2

;wait for heatup
M116 P0

M98 P"t0wipe.g"
	
G1 R2 Z0


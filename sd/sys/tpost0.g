; tpost0.g
;PCF fan on
M106 R2

G90
G1 X-15 F6000

;wait for heatup
M116 P0

if heat.heaters[tools[0].heaters[0]].current > 170
	G92 E0
	G1 E8 F320
	G92 E0
	;G1 E-0.5 F2500
	
G1 R2 Z0


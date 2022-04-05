var active = heat.heaters[tools[0].heaters[0]].active
var current = heat.heaters[tools[0].heaters[0]].current
var do_purge={var.active >= 170}
set var.do_purge=false

M280 P1 S100

G90
G1 X{global.t0purge_x} Y{global.t0purge_y} F{global.speed_xy}

;wait for heatup
if {var.current < var.active}
    M116 P0

if {var.do_purge}
	G92 E0
	G1 E{global.t0purge_amt} F{global.t0purge_speed}
	G92 E0
	G1 E{global.t0retract_amt} F{global.t0retract_speed}
    
    M280 P1 S10
    G4 P500
    M280 P1 S100
    
    G1 Y{global.t0purge_y-15} F{global.speed_xy}

    G1 X{global.t0wipe_max}
    G1 X{global.t0wipe_min}
    G1 X{global.t0wipe_max}
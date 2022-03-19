var do_purge={heat.heaters[tools[1].heaters[0]].current > 170}

G90
G53 G1 X{global.t1wipe_max} F{global.speed_xy}

if {var.do_purge}
	G92 E0
	G1 E{global.t1purge_amt} F{global.t1purge_speed}
	G92 E0
	G1 E{global.t1retract_amt} F{global.t1retract_speed}
    
    G53 G1 X{global.t1wipe_min} F{global.speed_xy}
    G53 G1 X{global.t1wipe_max}
    G53 G1 X{global.t1wipe_min}
    G53 G1 X{global.t1wipe_max}
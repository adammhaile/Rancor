var active = heat.heaters[tools[0].heaters[0]].active
var current = heat.heaters[tools[0].heaters[0]].current
var do_purge={var.active >= 170}

G90
G53 G1 X{global.t0wipe_max} F{global.speed_xy}

;wait for heatup
if {var.current < var.active}
    M116 P0

if {var.do_purge}
    G92 E0
    G1 E{global.t0purge_amt} F{global.t0purge_speed}
    G92 E0
    G1 E{global.t0retract_amt} F{global.t0retract_speed}
    
    G53 G1 X{global.t0wipe_min} F{global.speed_xy}
    G91
    G1 Y25
    G90
    G53 G1 X{global.t0wipe_max}
    G53 G1 X{global.t0wipe_min}
    G53 G1 X{global.t0wipe_max}
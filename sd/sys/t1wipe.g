var active = heat.heaters[tools[1].heaters[0]].active
var current = heat.heaters[tools[1].heaters[0]].current
var do_purge={var.active >= 170}

G90
G53 G1 X{global.t1wipe_max} F{global.speed_xy}

;wait for heatup
if {var.current < var.active}
    M116 P1

if {var.do_purge && !global.disable_purge}
    G92 E0
    G1 E{global.t1purge_amt} F{global.t1purge_speed}
    G92 E0
    G1 E{global.t1retract_amt} F{global.t1retract_speed}
    
    G53 G1 X{global.t1wipe_min} F{global.speed_xy}
    G91
    G1 Y25
    G90
    G53 G1 X{global.t1wipe_max}
    G53 G1 X{global.t1wipe_min}
    G53 G1 X{global.t1wipe_max}
; CHT 1.8mm Nozzle
; set base tool offsets
if {param.S} == 0
    set global.t0_x = 0
    set global.t0_y = 0
    set global.t0_z = 0.15
    set global.t0purge_amt = 25
    set global.t0purge_speed = 750
    set global.t0retract_amt = 0
    set global.t0retract_speed = 2400
    set global.t0prime = "default"
else
    set global.t1_x = 0
    set global.t1_y = 0
    set global.t1_z = 0
    set global.t1purge_amt = 12
    set global.t1purge_speed = 300
    set global.t1retract_amt = 0
    set global.t1retract_speed = 2400
    set global.t1prime = "default"
    
; set heater config
; S+1 because heater numbering is offset from tool number
M307 H{param.S+1} R2.616 K0.237:0.348 D5.69 E1.35 S1.00 B0 V23.9
M143 H{param.S+1} S285

; set base pressure advance
M572 D{param.S} S0
; set base retraction
M207 P{param.S} S0.5 R0 F2400 Z0.5
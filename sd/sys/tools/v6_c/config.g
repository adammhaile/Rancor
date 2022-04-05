; set base tool offsets
if {param.S} == 0
    set global.t0_x = 0
    set global.t0_y = 0
    set global.t0_z = 0.15
else
    set global.t1_x = 0
    set global.t1_y = 0
    set global.t1_z = 0
    
; set heater config
; S+1 because heater numbering is offset from tool number
M307 H{param.S+1} R2.616 K0.237:0.348 D5.69 E1.35 S1.00 B0 V23.9
M143 H{param.S+1} S285

; set base pressure advance
M572 D{param.S} S0
; set base retraction
M207 P{param.S} S0.5 R0 F2400 Z0.5

; set base tool offsets
if {param.S} == 0
    set global.t0_x = -71.5
    set global.t0_y = -20.6
    set global.t0_z = 0
else
    set global.t1_x = -0.3
    set global.t1_y = -20.6
    set global.t1_z = 0.35
    

; set base pressure advance
M572 D{param.S} S0
; set base retraction
M207 P{param.S} S0.5 R0 F2400 Z0.5
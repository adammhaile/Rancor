; pause.g
M800 F"pause"
M83            ; relative extruder moves
G1 E-3 F3600   ; retract 5mm of filament
G91
G1 Z{global.zclearance} F{global.speed_z}
G90

M98 P"full_park.g"


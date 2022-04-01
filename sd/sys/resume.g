; resume.g
M800 F"resume"
G1 R1 X0 Y0 Z5 {global.speed_xy} ; go to 5mm above position of the last print move
G1 R1 X0 Y0 Z0       ; go back to the last print move
M83                  ; relative extruder moves
G1 E3 F3600         ; extrude 10mm of filament


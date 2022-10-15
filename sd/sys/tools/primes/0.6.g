G90
G1 X0.0 Y2.0 Z1.0 F8000.0 ; prepare to prime
G92 E0 ; reset extrusion distance
G1 Z0.2 F1000.0
G1 X60.0 E9.0  F1000.0 ; priming
G1 X125.0 E12.5  F1000.0 ; priming
G1 Z0.5 F1000.0
G92 E0 ; reset extrusion distance
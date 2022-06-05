M4202 ; trigger camera video record start
G4 S1 ; wait for recording to start
T-1
M98 P"full_park.g"
G53 G1 X{global.t0park} U{global.t1park} Y{global.ypark} Z5 F{global.speed_xy}

M400  ; wait for rise to complete
M4203 ; stop video record
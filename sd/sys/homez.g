;homez.g
G29 S2
T0              ;always home with T0

G91             ;relative mode
G1 Z5 F800 H2   ;lower the bed
G90             ;absolute mode

; use G53 below because it needs to be relative to the probe
G53 G1 X165 Y160 F5000 ;position probe above center

M558 F500
G30

M558 F50
G30

G29 S1
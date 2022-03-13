; homeall.g

T0 P0

G91                     ; relative positioning
G1 H2 Z5 F6000          ; lift Z relative to current position
G1 H1 X-500 U500 Y-500 F1800  ; move quickly to X and Y axis endstops and stop there (first pass)
G1 H2 X5 U-5 Y5 F3000      ; go back a few mm
G1 H1 X-500 U500 Y-500 F360   ; move slowly to X and Y axis endstops once more (second pass)

G1 X1 Y1 U-1 F3000
G90                     ; absolute positioning

; use G53 below because it needs to be relative to the probe
G53 G1 X165 Y160 F5000 ;position probe above center

M558 F500
G30

M558 F50
G30

; Uncomment the following lines to lift Z after probing
;G91                    ; relative positioning
;G1 Z5 F100             ; lift Z relative to current position
;G90                    ; absolute positioning



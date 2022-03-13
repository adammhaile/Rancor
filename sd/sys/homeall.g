; homeall.g

T0 P0

G91                                 ; relative positioning
G1 H2 Z{global.zclearance} F{global.speed_xy}     ; lift Z relative to current position
G1 H1 X{-global.xu_seek} U{global.xu_seek} Y{-global.y_seek} F{global.speed_xyhome_fast}        ; move quickly to X and Y axis endstops and stop there (first pass)
G1 H2 X5 U-5 Y5 F{global.speed_xy/2}               ; go back a few mm
G1 H1 X{-global.xu_seek} U{global.xu_seek} Y{-global.y_seek} F{global.speed_xyhome_slow}         ; move slowly to X and Y axis endstops once more (second pass)

G1 X1 Y1 U-1 F{global.speed_xy/2}   ; back off from endstops
G90                                 ; absolute positioning

; use G53 below because it needs to be relative to the probe
G53 G1 X{global.xcenter} Y{global.ycenter} F{global.speed_xy} ;position probe above center

M558 F{global.speed_zhome_fast}
G30

M558 F{global.speed_zhome_slow}
G30

G91
G1 Z{global.zclearance} F{global.speed_z}
G90



; homex.g
; called to home the X axis
;
; generated by RepRapFirmware Configuration Tool v3.3.10 on Mon Feb 14 2022 00:04:10 GMT-0500 (Eastern Standard Time)
G91               ; relative positioning
G1 H2 Z5 F{global.speed_z}    ; lift Z relative to current position
G1 H1 U{global.xu_seek} F{global.speed_xyhome_fast} ; move quickly to X axis endstop and stop there (first pass)
G1 H2 U-5 F{global.speed_xy/2}    ; go back a few mm
G1 H1 U{global.xu_seek} F{global.speed_xyhome_slow}  ; move slowly to X axis endstop once more (second pass)
G1 H2 U-1 F{global.speed_xy/2}    ; go back a few mm
G1 H2 Z-5 F{global.speed_z}   ; lower Z again
G90               ; absolute positioning


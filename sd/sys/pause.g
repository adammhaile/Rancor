; pause.g
; called when a print from SD card is paused
;
; generated by RepRapFirmware Configuration Tool v3.3.10 on Mon Feb 14 2022 00:04:10 GMT-0500 (Eastern Standard Time)
M83            ; relative extruder moves
G1 E-3 F3600   ; retract 5mm of filament
G91
G1 Z{global.zclearance} F{global.speed_z}
G90

M98 P"full_park.g"


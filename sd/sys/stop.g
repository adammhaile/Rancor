; stop.g
; called when M0 (Stop) is run (e.g. when a print from SD card is cancelled)
;
; generated by RepRapFirmware Configuration Tool v3.3.10 on Mon Feb 14 2022 00:04:11 GMT-0500 (Eastern Standard Time)

M4202 ; trigger camera video record start
G4 S2 ; wait for recording to start

M800 F"complete"
M98 P"complete.g"
M98 P"present.g"

M400  ; wait for rise to complete
M4203 ; stop video record
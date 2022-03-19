M291 P"Please wait for temperature to be reached" R"Filament Unload" T5
M116
M291 P"Unloading and purging filament..." R"Filament Unload" T5
M308                ; Relative Extruder Moves
G92 E0              ; set extruder to 0

if {param.S} == 0
    M98 P{"tools/" ^ global.t0tool ^ "/unload.g"}
else
    M98 P{"tools/" ^ global.t1tool ^ "/unload.g"}
    
M400                ; Wait for the moves to finish
G92 E0              ; set extruder to 0
M292                ; Hide the message again
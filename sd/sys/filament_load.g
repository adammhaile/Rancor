M291 P"Please wait for temperature to be reached" R"Filament Load" T5
M116
M291 P"Loading and purging filament..." R"Filament Load" T5
M83                 ; Relative Extruder Moves
G92 E0              ; set extruder to 0

if {state.currentTool} == 0
    M98 P{"tools/" ^ global.t0tool ^ "/load.g"}
else
    M98 P{"tools/" ^ global.t1tool ^ "/load.g"}
    
M400                ; Wait for the moves to finish
G92 E0              ; set extruder to 0
M292                ; Hide the message again
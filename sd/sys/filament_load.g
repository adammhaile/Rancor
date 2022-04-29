var active = heat.heaters[tools[state.currentTool].heaters[0]].active
var current = heat.heaters[tools[state.currentTool].heaters[0]].current

if {var.current < var.active}
    M291 P"Please wait for temperature to be reached" R"Filament Load" T15
    M116 P{state.currentTool}

M291 S2 P"Press OK to continue loading" R"Filament Load"
M291 P"Loading and purging filament..." R"Filament Load" T15
M83                 ; Relative Extruder Moves
G92 E0              ; set extruder to 0

M800 F"filament_load"
if {state.currentTool} == 0
    M98 P{"tools/" ^ global.t0tool ^ "/load.g"}
else
    M98 P{"tools/" ^ global.t1tool ^ "/load.g"}
    
M400                ; Wait for the moves to finish
G92 E0              ; set extruder to 0
M292                ; Hide the message again
if {param.F} == "PLA"
    M572 D{state.currentTool} S0
    M207 P{state.currentTool} S0.5 R0 F2400 Z0.5
else
    M572 D{state.currentTool} S0
    M207 P{state.currentTool} S0.5 R0 F2400 Z0.5
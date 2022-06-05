if {param.F} == "PLA"
    M572 D{state.currentTool} S0.025
    M207 P{state.currentTool} S1.0 R0 F4000 Z0.25
elif {param.F} == "PETG"
    M572 D{state.currentTool} S0.05
    M207 P{state.currentTool} S1.0 R0 F4000 Z0.25
else
    M572 D{state.currentTool} S0
    M207 P{state.currentTool} S0.5 R0 F2400 Z0.5
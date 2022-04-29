; set base pressure advance
M572 D{state.currentTool} S0
; set base retraction
M207 P{state.currentTool} S0.5 R0 F2400 Z0.5
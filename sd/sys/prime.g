if {state.currentTool} == 0
    M98 P{"tools/primes/" ^ global.t0prime ^ ".g"}
else
    M98 P{"tools/primes/" ^ global.t1prime ^ ".g"}
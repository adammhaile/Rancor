; run base tool configs to populate globals
M98 P{"tools/" ^ global.t0tool ^ "/config.g"} S0
M98 P{"tools/" ^ global.t1tool ^ "/config.g"} S1
M98 P{"tools/bedoffsets.g"}

; setup T0 offsets
var x0 = {global.offset_probe_x + global.t0_x}
var y0 = {global.offset_probe_y + global.t0_y}
var z0 = {global.offset_probe_z + global.t0_z + global.offset_bed}

G10 P0 X{var.x0} Y{var.y0} Z{var.z0}

; setup T1 offsets
set var.x0 = {global.t1_x} ; T1 doesn't need a probe offset for X
set var.y0 = {global.offset_probe_y + global.t1_y}
set var.z0 = {global.offset_probe_z + global.t1_z + global.offset_bed}

G10 P1 U{var.x0} Y{var.y0} Z{var.z0}
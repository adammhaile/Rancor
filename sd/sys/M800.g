var file = "*" ^ {param.F}
if {param.F} != "layer" || ({param.F} == "layer" && global.allow_layer_msg == true)
    M118 P5 S{var.file}
; elif {param.F} == "layer" && global.allow_layer_msg == true
;     M118 P5 S{var.file}
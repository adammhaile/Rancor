var msg = "Configuring Bed for "^{param.F}
M291 P{var.msg} R"Bed Provisioning Init"

echo >"tools/bed.g" "set global.bed = """^{param.F}^""""
M98 P"tools/bed.g" 
M98 P"tools/setup.g"

set var.msg = "🎉🎉 Bed is set to use  "^{param.F}
M291 P{var.msg} R"Bed Provisioning Success"
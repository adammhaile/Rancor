var msg = "Configuring T0 for "^{param.F}
M291 P{var.msg} R"Tool Provisioning Init"

echo >"tools/t0.g" "set global.t0tool = """^{param.F}^""""
M98 P"tools/t0.g" 
M98 P"tools/setup.g"

set var.msg = "🎉🎉 T0 is set to use  "^{param.F}
M291 P{var.msg} R"Tool Provisioning Success"
var msg = "Configuring T1 for "^{param.F}
M291 P{var.msg} R"Tool Provisioning Init"

echo >"tools/t1.g" "set global.t1tool = """^{param.F}^""""
M98 P"tools/t1.g" 
M98 P"tools/setup.g"

set var.msg = "🎉🎉 T1 is set to use  "^{param.F}
M291 P{var.msg} R"Tool Provisioning Success"
;base values
global offset_probe_x = -71.5
global offset_probe_y = -20.6
global offset_probe_z = 0
global offset_bed = 0

;tool selection
global cur_tool = "default"
global t0tool = {global.cur_tool}
global t1tool = {global.cur_tool}

;filament selection


;size setup
global xsize = 330
global ysize = 320
global zsize = 600

global xcenter = {global.xsize/2}
global ycenter = {global.ysize/2}

global xu_seek = 500
global y_seek = 500

;positions and distances
global zclearance = 3
global t0park = -84
global t1park = 449
global ypark = 340

;speeds
global speed_xy = 8000
global speed_xyhome_fast = 1800
global speed_xyhome_slow = 360
global speed_z = 3000
global speed_zhome_fast = 500
global speed_zhome_slow = 50

;T0 params
global t0_x=0
global t0_y=0
global t0_z=0

global t0purge_x = -54
global t0purge_y = 275
global t0purge_amt = 12
global t0purge_speed = 300
global t0wipe_max = -38
global t0wipe_min = -48
global t0retract_amt = 0
global t0retract_speed = 2400

;T1 params
global t1_x=0
global t1_y=0
global t1_z=0

global t1purge_amt = 12
global t1purge_speed = 300
global t1wipe_max = 408
global t1wipe_min = 422
global t1retract_amt = 0
global t1retract_speed = 2400

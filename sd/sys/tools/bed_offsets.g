if {global.bed == "fulament_smooth"}
    set global.offset_bed = -0.38
elif {global.bed == "fulament_textured"}
    set global.offset_bed = -0.06
else
    set global.offset_bed = 0.0
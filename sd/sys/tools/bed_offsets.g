if {global.bed == "fulament_smooth"}
    set global.offset_bed = 0.0
elif {global.bed == "fulament_textured"}
    set global.offset_bed = 0.32
else
    set global.offset_bed = 0.0
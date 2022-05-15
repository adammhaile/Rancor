if {global.bed == "fulament_smooth"}
    echo "smooth"
    set global.offset_bed = 0.0
elif {global.bed == "fulament_textured"}
    echo "textured"
    set global.offset_bed = 0.32
else
    echo "else"
    set global.offset_bed = 0.0
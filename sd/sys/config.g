; Load global vars
M98 P"globals.g"

; General preferences
G90                                                         ; send absolute coordinates...
M83                                                         ; ...but relative extruder moves
M550 P"Rancor"                                              ; set printer name

; Larson VU Serial Config
M575 P1 B57600 S2                                           ; Setup UART on IO_0 to 57600 baud

; Audio Player Serial Config
M575 P2 B57600 S2                                           ; Setup UART on IO_1 to 57600 baud

; Setup Lights
M950 P0 C"0.out9" Q4000

; Setup Servos
M950 S1 C"0.io7.out"
M280 P1 S100

; Wait a moment for the CAN expansion boards to start
G4 S2

; Drives
M569 P0.0 S0                                                ; Left Y
M569 P0.1 S1                                                ; Left X
M569 P0.2 S0                                                ; Left Extruder
M569 P0.3 S1                                                ; Left Z
M569 P0.4 S1                                                ; Right Rear Z
M569 P0.5 S1                                                ; Right Front Z
M569 P1.0 S1                                                ; Right Y
M569 P1.1 S1                                                ; Right X
M569 P1.2 S0                                                ; Right Extruder

M584 X0.1 U1.1 Y0.0:1.0 Z0.3:0.4:0.5 E0.2:1.2               ; set drive mapping
M350 X16 U16 Y16 Z16 E16:16 I1                              ; configure microstepping with interpolation
M92  X160 U160 Y160 Z1600 E397:397                          ; set steps per mm
M566 X400 U400 Y400 Z100 E1500:1500                         ; set maximum instantaneous speed changes (mm/min)
M203 X10800 U10800 Y10800 Z900 E3600:3600                   ; set maximum speeds (mm/min)
M201 X500 U500 Y500 Z100 E1500                             	; set accelerations (mm/s^2)
M906 X1400 U1400 Y1400 Z1200 E1100:1100 I75                 ; set motor currents (mA) and motor idle factor in per cent
;M84 S30                                                    ; Set idle timeout

;Leadscrew locations
M671 X-13.7:343.8:343.8 Y160:287.5:32.5 S7.5

; Axis Limits
; TODO - these are wild guesses at this point for X
; will need to change mins to negatives
M208 S1 X-85 U0 Y0 Z-2                                            ; set axis minima
M208 S0 X405 U450 Y345 Z{global.zsize}                            ; set axis maxima

; Endstops
M574 X1 S1 P"0.io2.in"                                        ; X homes low end
M574 U2 S1 P"1.io2.in"                                        ; U homes high end
M574 Y1 S1 P"0.io3.in+1.io3.in"                               ; Y has dual motors and endstops
; TODO - setup homing files https://duet3d.dozuki.com/Wiki/ConfiguringMultipleIndependentXcarriagesCartesian#Section_Homing_files

; Z-Probe
M558 P5 C"^0.io5.in" H2.5 F250 T6000                            ; set Z probe type to switch and the dive height + speeds
G31 P500 X0 Y0 Z1.2                                   ; set Z probe trigger value, offset and trigger height
M557 X15:315 Y20:300 S75:70                                    ; define mesh grid

; Heaters
; Bed
M308 S0 P"0.temp0" Y"thermistor" T100000 B4240                ; configure sensor 0 as thermistor on pin temp0
M950 H0 C"0.out0" T0                                          ; create bed heater output on out0 and map it to sensor 0
M307 H0 B0 R0.611 C647.0 D2.25 S1.00                          ; enable bang-bang mode for the bed heater and set PWM limit
M140 H0                                                     ; map heated bed to heater 0
M143 H0 S120                                                ; set temperature limit for heater 0 to 120C

; Left
M308 S1 P"0.temp1" Y"thermistor" T100000 B4725 C7.06e-8       ; configure sensor 1 as thermistor on pin temp1
M950 H1 C"0.out1" T1                                          ; create nozzle heater output on out1 and map it to sensor 1
; M307 H1 R2.616 K0.237:0.348 D5.69 E1.35 S1.00 B0 V23.9      ; disable bang-bang mode for heater  and set PWM limit
; M143 H1 S285                                                ; set temperature limit for heater 1 to 280C

; Right
M308 S2 P"1.temp0" Y"thermistor" T100000 B4725 C7.06e-8     ; configure sensor 2 as thermistor on pin 1.temp0
M950 H2 C"1.out0" T2                                        ; create nozzle heater output on 1.out0 and map it to sensor 2
; M307 H1 R2.616 K0.237:0.348 D5.69 E1.35 S1.00 B0 V23.9      ; disable bang-bang mode for heater  and set PWM limit
; M143 H2 S285                                                ; set temperature limit for heater 2 to 280C

; Fans
; left HEF
M950 F0 C"0.out7"                                             ; create fan 0 on pin out7 and set its frequency
M106 P0 S1 H1 T45                                         ; set fan 0 value. Thermostatic control is turned on
; Left PCF
M950 F1 C"0.out8"                                             ; create fan 1 on pin out8 and set its frequency
M106 P1 S0 H-1                                              ; set fan 1 value. Thermostatic control is turned off
; Right HEF
M950 F2 C"1.out7"                                           ; create fan 2 on pin 1.out7 and set its frequency
M106 P2 S1 H2 T45                                         ; set fan 2 value. Thermostatic control is turned on
; Right PCF
M950 F3 C"1.out8"                                           ; create fan 3 on pin 1.out8 and set its frequency
M106 P3 S0 H-1                                               ; set fan 3 value. Thermostatic control is turned on

; Tools
; Left
M563 P0 S"Left" D0 X0 H1 F1                                    ; define tool 0
; G10 P0 X-71.5 Y-20.6 Z0                                        ; set tool 0 axis offsets
G10 P0 X0 Y0 Z0
G10 P0 R0 S0                                                   ; set initial tool 0 active and standby temperatures to 0C

M591 D0 P1 C"0.io4.in" S0								; setup T0 filament sensor

; Right
M563 P1 S"Right" D1 X3 H2 F3                                   ; define tool 1
; G10 P1 U-0.3 Y-20.6 Z0.35                                      ; set tool 1 axis offsets
G10 P1 U0 Y0 Z0
G10 P1 R0 S0                                                   ; set initial tool 1 active and standby temperatures to 0C

M591 D1 P1 C"1.io5.in" S0								; setup T1 filament sensor

; extra sensors
M308 S10 Y"mcu-temp" A"MCU"                           ; defines sensor 10 as MCU temperature sensor

; set base tool names
M98 P"tools/t0.g" 
M98 P"tools/t1.g"
M98 P"tools/bed.g"

; load variable tool configs
M98 P"tools/setup.g"

; Ensure T0 loaded
M98 P"soft_load_tool.g" S0

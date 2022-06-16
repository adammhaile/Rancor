# Rancor 3D Printer

Rancor is a project that came about from being inspired by seeing all the awesome projects at MRRF 2021 and is my first ground-up 3D printer design. It is an IDEX machine with a "spared no expense" and "there's no such thing as too much feature creep" design philosophy. Learning to CNC machine aluminium with my new [MilkCr8 CNC](https://github.com/Makers-On-Tap/milkcr8-cnc) was also a major factor, so if a component *could* be machined out of 1/4" aluminum tooling plate, it was. It was never designed to be manufactured and mainly exists as somethingt to show off.

## Specs

- Cartesian IDEX motion system
- 45 parts custom machined from aluminum tooling plate
- Cold-swappable tools require only 3 bolts and a 14-pin Molex Mini-Fit connector
- 5 currently configured tools that can be used
    - 2x E3D Hemera & Revo
    - 3x E3D Hemera & copper block, Slice 50W heater, Bondtech CHT nozzle (1.0mm, 1.4mm, 1.8mm)
- 330x320x600 mm print volume
- Prusa SuperPINDA ABL probe
- 0.9° LDO 42STH60-2004MAC Motors for each axis
- LDO MGN12 Linear Rails
- PTFE coated LDO leadscrews for Z
- Mandala Rose Works 6.35mm MIC6 cast aluminum bed (Railcore)
- Mandala Rose Works Z axis bed yokes (Railcore)
- Mandala Rose Works Z Oldham Wobblers (Railcore)
- 750W 120V AC Keenovo Bed Heater
- Duet 6HC mainboard with Duet 3HC expansion to drive all 9 motors
- 930x550x960 mm outter dimensions (excluding tool cables)
- 7.9" 400x1280 LCD display for g-code scrolling
- 13.3" 1080x1920 LCD touch display to show the Duet DWC interface
- 2x Raspberry Pi 4 - One for Duet SBC and one running Android for DWC display
- Filament sensors for each tool, based on the Prusa Mini sensor
- Internal network between the two Pi 4's using a Linksys router that provides on-site WiFi
- Ethernet connection for Duet SBC Pi for normal network connectivity
- Teensy 3.2 managed "voice" output controlled via a Duet UART connection


## FAQ


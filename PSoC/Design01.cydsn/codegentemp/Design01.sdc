# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\mac_000\Documents\Git_IR_REMO\PSoC\Design01.cydsn\Design01.cyprj
# Date: Fri, 21 Aug 2020 00:16:38 GMT
#set_units -time ns
create_clock -name {Clock_1(FFB)} -period 3750 -waveform {0 1875} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {CyILO} -period 25000 -waveform {0 12500} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 25000 -waveform {0 12500} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 31.25 -waveform {0 15.625} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 62.5 -waveform {0 31.25} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 62.5 -waveform {0 31.25} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 61 121} [list]


# Component constraints for C:\Users\mac_000\Documents\Git_IR_REMO\PSoC\Design01.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\mac_000\Documents\Git_IR_REMO\PSoC\Design01.cydsn\Design01.cyprj
# Date: Fri, 21 Aug 2020 00:16:37 GMT

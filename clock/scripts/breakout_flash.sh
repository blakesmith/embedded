#!/bin/sh

OPENOCD=openocd
OPENOCD_CONFIG=$1
HEX=$2

$OPENOCD -f "/usr/share/openocd/scripts/interface/jlink.cfg" \
         -c "transport select swd" \
         -c "reset_config none separate" \
         -f $OPENOCD_CONFIG \
         -c "init" \
         -c "reset halt" \
         -c "flash write_image erase $HEX"



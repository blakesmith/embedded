#!/bin/sh

OPENOCD=openocd
OPENOCD_CONFIG=$1
HEX=$2

$OPENOCD -f "/usr/local/share/openocd/scripts/interface/jlink.cfg" \
         -c "transport select swd" \
         -f $OPENOCD_CONFIG \
         -c "reset_config none separate" \
         -c "init" \
         -c "targets" \
         -c "reset halt" \
         -c "flash write_image $HEX" \
         -c "reset run" \
         -c "exit"



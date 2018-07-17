#!/bin/sh

OPENOCD=openocd
OPENOCD_CONFIG=$1
HEX=$2

$OPENOCD -f $OPENOCD_CONFIG \
         -c "init" \
         -c "reset halt" \
         -c "flash write_image erase $HEX" \
         -c "reset run" \
         -c "exit"



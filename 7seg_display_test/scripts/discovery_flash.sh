#!/bin/sh

OPENOCD=openocd
OPENOCD_CONFIG=/usr/share/openocd/scripts/board/stm32f4discovery.cfg
HEX=$1

$OPENOCD -f $OPENOCD_CONFIG \
         -c "init" \
         -c "reset halt" \
         -c "flash write_image erase $HEX" \
         -c "reset run" \
         -c "exit"


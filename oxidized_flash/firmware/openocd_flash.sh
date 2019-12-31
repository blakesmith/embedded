#!/bin/sh

OPENOCD=openocd
OPENOCD_CONFIG=$1
HEX=$2

$OPENOCD -d -f "/usr/local/share/openocd/scripts/interface/jlink.cfg" \
         -c "transport select swd" \
	 -c "set CHIPNAME samd51g19a" \
         -f $OPENOCD_CONFIG \
         -c "reset_config none" \
         -c "init" \
         -c "targets" \
         -c "reset halt" \
         -c "flash write_image $HEX" \
         -c "reset run" \
         -c "exit"



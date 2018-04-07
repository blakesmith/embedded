#!/bin/sh

OPENOCD=openocd
OPENOCD_CONFIG=/usr/share/openocd/scripts/board/stm32f4discovery.cfg
HEX=bazel-out/armeabi-v7a-m4-fastbuild/bin/test_project/test.hex

$OPENOCD -f $OPENOCD_CONFIG \
         -c "init" \
         -c "reset halt" \
         -c "flash write_image erase $HEX" \
         -c "reset run" \
         -c "exit"


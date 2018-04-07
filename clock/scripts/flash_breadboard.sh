#!/bin/sh

OPENOCD=openocd
INTERFACE=/usr/share/openocd/scripts/interface/jlink.cfg
TARGET=/usr/share/openocd/scripts/target/stm32l1.cfg
HEX=bazel-out/clang_linux_arm_m3-fastbuild/bin/clock/clock.hex

$OPENOCD \
    -f $INTERFACE \
    -c "transport select swd" \
    -f $TARGET \
    -c "init" \
    -c "flash write_image erase $HEX" \
    -c "exit"


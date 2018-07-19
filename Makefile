all: nome_breadboard

nome_flash:
	./nome/scripts/flash_breadboard.sh

clean:
	bazel clean

display_test:
	bazel build \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--cpu=armeabi-v7a-m4 \
	--define TARGET=stm32f411 \
	//7seg_display_test:test

display_test_flash:
	bazel run \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--cpu=armeabi-v7a-m4 \
	--define TARGET=stm32f411 \
	//7seg_display_test/scripts:discovery_flash

nome_breadboard:
	bazel build \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--cpu=armeabi-v7a-m4 \
	--define TARGET=stm32f411 \
	//nome:nome

nome_prototype:
	bazel build \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--cpu=armeabi-v7a-m4 \
	--define TARGET=stm32f413 \
	//nome:nome

nome_linux:
	bazel run \
	--define TARGET=linux \
	//nome:nome_linux

clock_stm32:
	bazel build \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--cpu=armeabi-v7a-m3 \
	--define TARGET=stm32l1 \
	--strip=never \
	//clock:clock

clock_stm32_breakout:
	bazel run \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--strip=never \
	--cpu=armeabi-v7a-m3 \
	--define TARGET=stm32l1 \
	//clock/scripts:breakout_flash

keebee_stm32:
	bazel build \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--cpu=armeabi-v7a-m0 \
	--define TARGET=stm32f042 \
	//keebee:keebee

keebee_flash:
	bazel run \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--compilation_mode=dbg \
	--strip=never \
	--cpu=armeabi-v7a-m0 \
	--define TARGET=stm32f042 \
	//keebee:keebee_flash

scan_matrix:
	bazel build \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--cpu=armeabi-v7a-m0 \
	--define TARGET=stm32f042 \
	//drivers/stm32:scan_matrix

stm32f042_base:
	bazel build \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--cpu=armeabi-v7a-m0 \
	--define TARGET=stm32f042 \
	//third_party/STM/stm32f0/cube:base

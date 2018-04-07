all: nome_breadboard

nome_flash:
	./nome/scripts/flash_breadboard.sh

clean:
	bazel clean

display_test:
	bazel build \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--cpu=armeabi-v7a-m4 \
	--define TARGET=breadboard \
	//test_project:test

nome_breadboard:
	bazel build \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--cpu=armeabi-v7a-m4 \
	--define TARGET=breadboard \
	//nome:nome

nome_prototype:
	bazel build \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--cpu=armeabi-v7a-m4 \
	--define TARGET=prototype \
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
	//clock:clock

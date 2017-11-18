all: nome_breadboard

nome_flash:
	./nome/scripts/flash_breadboard.sh

clean:
	bazel clean

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

l1_drivers:
	bazel build \
	--crosstool_top=@stm32//tools/arm_compiler:toolchain \
	--cpu=armeabi-v7a-m3 \
	//third_party/STM/stm32l1:stm_std_periph

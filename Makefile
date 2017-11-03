all: nome_breadboard

nome_flash:
	./nome/scripts/flash_breadboard.sh

clean:
	bazel clean

drivers:
	bazel build --crosstool_top=@stm32//tools/arm_compiler:toolchain --cpu=armeabi-v7a //drivers:stm_drivers_breadboard

nome_breadboard:
	bazel build --crosstool_top=@stm32//tools/arm_compiler:toolchain --cpu=armeabi-v7a //nome:nome_breadboard

nome_prototype:
	bazel build --crosstool_top=@stm32//tools/arm_compiler:toolchain --cpu=armeabi-v7a //nome:nome_prototype


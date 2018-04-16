cc_binary(
    name = "test_stm32",
    srcs = [
        "src/startup_stm32f411xe.s",
        "src/stm32f4xx_it.h",
        "src/stm32f4xx_it.cc",
        "src/system_stm32f4xx.cc",
        "src/main.cc",
    ],
    copts = [
        "-fno-rtti",
        "-specs=nosys.specs",
        "-DSTM32F411xE",
    ],
    linkopts = [
        "-T7seg_display_test/linker_scripts/STM32F411RETx_FLASH.ld"
    ],
    deps = [
        "linker_scripts/STM32F411RETx_FLASH.ld",
        "//drivers/stm32:gpio_common",
        "//drivers/stm32:i2c_common",
        "//drivers/stm32:status_led",
        "//drivers/stm32:as1115_display",
        "//drivers/stm32:ht16K33_display"
    ],
    linkstatic = 1
)

load("//tools/arm_compiler:raw_binary.bzl", "hex_binary")

hex_binary(
    name = "test",
    src = ":test_stm32"
)

config_setting(
    name = "target_breadboard",
    define_values = {
        "TARGET": "breadboard"
    }
)

config_setting(
    name = "target_prototype",
    define_values = {
        "TARGET": "prototype"
    }
)


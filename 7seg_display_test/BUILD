cc_binary(
    name = "test_stm32",
    srcs = [
        "src/main.cc",
    ],
    copts = [
        "-fno-rtti",
        "-specs=nosys.specs",
        "-DSTM32F411xE",
    ],
    linkopts = [
        "-Tthird_party/STM/stm32f4/STM32F411RETx_FLASH.ld"
    ],
    deps = [
        "//third_party/STM/stm32f4:bin_common",
        "//third_party/STM/stm32f4:linker_script",
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

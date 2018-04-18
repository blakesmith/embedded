cc_binary(
    name = "clock_stm32",
    srcs = [
        "src/main.cc",
    ],
    copts = [
        "-fno-rtti",
        "-specs=nosys.specs",
        "-DSTM32L1XX_MD"
    ],
    linkopts = [
        "-Tthird_party/STM/stm32l1/STM32L151C8_FLASH.ld"
    ],
    deps = [
        "//third_party/STM/stm32l1:bin_common",
        "//third_party/STM/stm32l1:stm32l151_linker_script",
        "//drivers/stm32:gpio_common",
        "//drivers/stm32:i2c_common",
        "//drivers/stm32:rtc",
        "//drivers/stm32:as1115_display",
    ],
    linkstatic = 1
)

load("//tools/arm_compiler:raw_binary.bzl", "hex_binary")

hex_binary(
    name = "clock",
    src = ":clock_stm32"
)

cc_binary(
    name = "keebee_stm32",
    srcs = [
        "src/main.cc",
        "src/stm32f0xx_it.cc",
        "src/stm32f0xx_it.h",
    ],
    copts = [
        "-DSTM32F042x6",
        "-fno-rtti",
        "-specs=nosys.specs"
    ],
    linkopts = [
        "-Tthird_party/STM/stm32f0/STM32F042K6Tx_FLASH.ld"
    ],
    deps = [
        "//third_party/STM/stm32f0/common:common_bin",
        "//third_party/STM/stm32f0/cube:base",
        "//third_party/STM/stm32f0:stm32f042_linker_script",
        "//keebee/src/hid:keyboard"
    ],
    linkstatic = 1
)

load("//tools/arm_compiler:raw_binary.bzl", "hex_binary")

hex_binary(
    name = "keebee",
    src = ":keebee_stm32"
)



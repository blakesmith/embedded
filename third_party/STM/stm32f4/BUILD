licenses(["unencumbered"])

config_setting(
    name = "target_stm32f411",
    define_values = {
        "TARGET": "stm32f411"
    },
    visibility = ["//visibility:public"]
)

config_setting(
    name = "target_stm32f413",
    define_values = {
        "TARGET": "stm32f413"
    },
    visibility = ["//visibility:public"]
)

cc_library(
    name = "bin_common",
    srcs = [
        "common/startup_stm32f411xe.s",
        "common/stm32f4xx_it.cc",
        "common/system_stm32f4xx.cc"
    ],
    hdrs = [
        "common/stm32f4xx_it.h"
    ],
    deps = [
        ":stm_cmsis",
        ":stm_cmsis_device",
    ],
    copts = select({
        ":target_stm32f411": ["-DSTM32F411xE"],
        ":target_stm32f413": ["-DSTM32F413_423xx"]
    }),
    visibility = ["//visibility:public"]
)

cc_library(
    name = "stm_cmsis",
    hdrs = glob(["CMSIS/Include/*.h"]),
    strip_include_prefix = "CMSIS/Include/",
    visibility = ["//visibility:public"]
)

cc_library(
    name = "stm_cmsis_device",
    hdrs = glob(["CMSIS/Device/ST/STM32F4xx/Include/*.h"]),
    strip_include_prefix = "CMSIS/Device/ST/STM32F4xx/Include/",
    visibility = ["//visibility:public"]
)

cc_library(
    name = "stm_std_periph",
    srcs = glob(["STM32F4xx_StdPeriph_Driver/src/*.c"]),
    hdrs = glob(["STM32F4xx_StdPeriph_Driver/inc/*.h"]),
    strip_include_prefix = "STM32F4xx_StdPeriph_Driver/inc/",
    copts = [
        "-include stm32f4xx_conf.h",
    ] + select({
        ":target_stm32f411": ["-DSTM32F411xE"],
        ":target_stm32f413": ["-DSTM32F413_423xx"]
    }),
    visibility = ["//visibility:public"],
    deps = [
        ":stm_cmsis",
        ":stm_cmsis_device"
    ]
)

alias(
    name = "stm32f411_linker_script",
    actual = "STM32F411RETx_FLASH.ld",
    visibility = ["//visibility:public"]
)

alias(
    name = "stm32f413_linker_script",
    actual = "STM32F413CGUx_FLASH.ld",
    visibility = ["//visibility:public"]
)


licenses(["unencumbered"])

config_setting(
    name = "target_stm32l1",
    define_values = {
        "TARGET": "stm32l1"
    },
    visibility = ["//visibility:public"]
)

cc_library(
    name = "bin_common",
    srcs = [
        "common/startup_stm32l1xx_md.s",
        "common/system_stm32l1xx.cc"
    ],
    hdrs = [
        "common/system_stm32l1xx.h"
    ],
    deps = [
        "stm_cmsis",
        "stm_cmsis_device"
    ],
    copts = [
        "-DSTM32L1XX_MD"
    ],
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
    hdrs = glob(["CMSIS/Device/ST/STM32L1xx/Include/*.h"]),
    strip_include_prefix = "CMSIS/Device/ST/STM32L1xx/Include/",
    visibility = ["//visibility:public"]
)

cc_library(
    name = "stm_std_periph",
    srcs = glob(["STM32L1xx_StdPeriph_Driver/src/*.c"]),
    hdrs = glob(["STM32L1xx_StdPeriph_Driver/inc/*.h"]),
    strip_include_prefix = "STM32L1xx_StdPeriph_Driver/inc/",
    copts = [
        "-include stm32l1xx_conf.h",
        "-DSTM32L1XX_MD"
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":stm_cmsis",
        ":stm_cmsis_device"
    ]
)

alias(
    name = "stm32l151_linker_script",
    actual = "STM32L151C8_FLASH.ld",
    visibility = ["//visibility:public"]
)

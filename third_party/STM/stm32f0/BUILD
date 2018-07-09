licenses(["unencumbered"])

config_setting(
    name = "target_stm32f042",
    define_values = {
        "TARGET": "stm32f042",
    },
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
    hdrs = glob(["CMSIS/Device/ST/STM32F0xx/Include/*.h"]),
    strip_include_prefix = "CMSIS/Device/ST/STM32F0xx/Include/",
    visibility = ["//visibility:public"]
)

alias(
    name = "stm32f042_linker_script",
    actual = "STM32F042K6Tx_FLASH.ld",
    visibility = ["//visibility:public"]
)

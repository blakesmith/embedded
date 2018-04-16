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

config_setting(
    name = "target_stm32f411",
    define_values = {
        "TARGET": "stm32f411"
    }
)

config_setting(
    name = "target_stm32f413",
    define_values = {
        "TARGET": "stm32f413"
    }
)

config_setting(
    name = "target_stm32l1",
    define_values = {
        "TARGET": "stm32l1"
    }
)

STM_DRIVERS = select({
    ":target_breadboard": [
        "//third_party/STM/stm32f4:stm_cmsis",
        "//third_party/STM/stm32f4:stm_cmsis_device",
        "//third_party/STM/stm32f4:stm_std_periph",
    ],
    ":target_prototype": [
        "//third_party/STM/stm32f4:stm_cmsis",
        "//third_party/STM/stm32f4:stm_cmsis_device",
        "//third_party/STM/stm32f4:stm_std_periph",
    ],
    ":target_stm32f411": [
        "//third_party/STM/stm32f4:stm_cmsis",
        "//third_party/STM/stm32f4:stm_cmsis_device",
        "//third_party/STM/stm32f4:stm_std_periph",
    ],
    ":target_stm32f413": [
        "//third_party/STM/stm32f4:stm_cmsis",
        "//third_party/STM/stm32f4:stm_cmsis_device",
        "//third_party/STM/stm32f4:stm_std_periph",
    ],
    ":target_stm32l1": [
        "//third_party/STM/stm32l1:stm_cmsis",
        "//third_party/STM/stm32l1:stm_cmsis_device",
        "//third_party/STM/stm32l1:stm_std_periph",
    ]
})

COMMON_COPTS = select({
    ":target_breadboard": [
        "-fno-rtti",
        "-DSTM32F411xE",
        "-DTARGET_BREADBOARD"
    ],
    ":target_prototype": [
        "-fno-rtti",
        "-DSTM32F413_423xx",
        "-DTARGET_PROTOTYPE"
    ],
    ":target_stm32f411": [
        "-fno-rtti",
        "-DSTM32F411xE",
    ],
    ":target_stm32f413": [
        "-fno-rtti",
        "-DSTM32F413_423xx",
    ],
    ":target_stm32l1": [
        "-fno-rtti",
        "-DSTM32L1XX_MD"
    ]
})

cc_library(
    name = "gpio_common",
    srcs = [
        "gpio_pin.cc",
        "gpio_bus.cc",
    ],
    hdrs = [
        "gpio_pin.h",
        "gpio_bus.h",
    ],
    copts = COMMON_COPTS,
    deps = STM_DRIVERS,
    visibility = ["//visibility:public"]
)

cc_library(
    name = "i2s_common",
    srcs = [
        "i2s_transmitter.cc",
    ],
    hdrs = [
        "i2s_transmitter.h",
    ],
    copts = COMMON_COPTS,
    deps = STM_DRIVERS + [
        ":gpio_common"
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "i2c_common",
    srcs = [
        "i2c_bus.cc",
    ],
    hdrs = [
        "i2c_bus.h",
    ],
    copts = COMMON_COPTS,
    deps = STM_DRIVERS + [
        ":gpio_common"
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "cs43l22_dac",
    srcs = [
        "cs43l22_dac.cc"
    ],
    hdrs = [
        "cs43l22_dac.h"
    ],
    copts = COMMON_COPTS,
    deps = [
        ":i2c_common",
        ":i2s_common"
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "as1115_display",
    srcs = [
        "as1115_display.cc",
        "display_7seg.cc"
    ],
    hdrs = [
        "as1115_display.h",
        "display_7seg.h"
    ],
    copts = COMMON_COPTS,
    deps = [
        ":i2c_common"
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "ht16K33_display",
    srcs = [
        "ht16K33_display.cc",
        "display_7seg.cc"
    ],
    hdrs = [
        "ht16K33_display.h",
        "display_7seg.h"
    ],
    copts = COMMON_COPTS,
    deps = [
        ":i2c_common"
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "pec11_encoder",
    srcs = [
        "pec11_renc.cc"
    ],
    hdrs = [
        "pec11_renc.h"
    ],
    copts = COMMON_COPTS,
    deps = [
        ":gpio_common"
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "status_led",
    srcs = [
        "status_led.cc"
    ],
    hdrs = [
        "status_led.h"
    ],
    copts = COMMON_COPTS,
    deps = [
        ":gpio_common"
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "rtc",
    srcs = [
        "rtc.cc"
    ],
    hdrs = [
        "rtc.h"
    ],
    copts = COMMON_COPTS,
    deps = STM_DRIVERS,
    visibility = ["//visibility:public"]
)

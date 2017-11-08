cc_library(
    name = "protocol_common",
    srcs = [
        "gpio_pin.cc",
        "gpio_bus.cc",
        "i2c_bus.cc",
        "i2s_transmitter.cc"
    ],
    hdrs = [
        "gpio_pin.h",
        "gpio_bus.h",
        "i2c_bus.h",
        "i2s_transmitter.h"
    ],
    copts = select({
        ":target_breadboard": [
            "-fno-rtti",
            "-DSTM32F411xE"
        ],
        ":target_prototype": [
            "-fno-rtti",
            "-DSTM32F413_423xx"
        ]
    }),
    deps = [
        "//third_party/STM:stm_cmsis",
        "//third_party/STM:stm_cmsis_device",
        "//third_party/STM:stm_std_periph",
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
    copts = select({
        ":target_breadboard": [
            "-fno-rtti",
            "-DSTM32F411xE",
            "-DTARGET_BREADBOARD"
        ],
        ":target_prototype": [
            "-fno-rtti",
            "-DSTM32F413_423xx",
            "-DTARGET_PROTOTYPE"
        ]
    }),
    deps = [
        ":protocol_common"
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
    copts = select({
        ":target_breadboard": [
            "-fno-rtti",
            "-DSTM32F411xE"
        ],
        ":target_prototype": [
            "-fno-rtti",
            "-DSTM32F413_423xx"
        ]
    }),
    deps = [
        ":protocol_common"
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
    copts = select({
        ":target_breadboard": [
            "-fno-rtti",
            "-DSTM32F411xE"
        ],
        ":target_prototype": [
            "-fno-rtti",
            "-DSTM32F413_423xx"
        ]
    }),
    deps = [
        ":protocol_common"
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
    copts = select({
        ":target_breadboard": [
            "-fno-rtti",
            "-DSTM32F411xE"
        ],
        ":target_prototype": [
            "-fno-rtti",
            "-DSTM32F413_423xx"
        ]
    }),
    deps = [
        ":protocol_common"
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
    copts = select({
        ":target_breadboard": [
            "-fno-rtti",
            "-DSTM32F411xE"
        ],
        ":target_prototype": [
            "-fno-rtti",
            "-DSTM32F413_423xx"
        ]
    }),
    deps = [
        ":protocol_common"
    ],
    visibility = ["//visibility:public"]
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

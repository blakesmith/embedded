cc_library(
    name = "keyboard",
    hdrs = glob(["*.h"]),
    srcs = glob(["*.c"]),
    deps = [
        "//third_party/STM/stm32f0/usb:core",
        "//third_party/STM/stm32f0/cube:base",
    ],
    copts = [
        "-DSTM32F042x6",
    ],
    visibility = ["//visibility:public"]
)


licenses(["unencumbered"])

cc_library(
    name = "core",
    hdrs = glob(["Core/Inc/*.h"]),
    srcs = glob(["Core/Src/*.c"]),
    strip_include_prefix = "Core/Inc/",
    visibility = ["//visibility:private"]
)

cc_library(
    name = "hid_keyboard_device_desc",
    hdrs = [
        "Class/HID/keyboard/usbd_desc.h",
    ],
    deps = [
        ":core"
    ],
    strip_include_prefix = "Class/HID/keyboard/",
    visibility = ["//visibility:public"]
)

cc_library(
    name = "hid_keyboard",
    hdrs = [
        "Class/HID/Inc/usbd_hid.h",
    ],
    srcs = [
        "Class/HID/Src/usbd_hid.c",
    ],
    deps = [
        ":core",
        ":hid_keyboard_device_desc"
    ],
    strip_include_prefix = "Class/HID/Inc/",
    visibility = ["//visibility:private"]
)


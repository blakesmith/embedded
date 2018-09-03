cc_library(
    name = "ui",
    hdrs = [
        "input_event.h",
        "ui.h",
        "x11_display.h",
        "x11_input.h"
    ],
    srcs = [
        "input_event.cc",
        "ui.cc",
        "x11_display.cc",
        "x11_input.cc"
    ],
    visibility = [
        "//keebird/src:__pkg__"
    ],
    deps = [
        "//keebird/src/synth:synth",
        "//keebird/src/util:log"
    ],
    linkopts = [
        "-lX11"
    ]
)

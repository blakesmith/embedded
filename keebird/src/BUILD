cc_binary(
    name = "keebird_linux",
    srcs = [
        "adsr_envelope.h",
        "adsr_envelope.cc",
        "beat.h",
        "beat.cc",
        "alsa_output.h",
        "alsa_output.cc",
        "main_linux.cc",
        "mixer.h",
        "osc.h",
        "osc.cc",
    ],
    visibility = [
        "//visibility:public"
    ],
    linkopts = [
        "-lasound"
    ]
)

cc_binary(
    name = "keebird_linux",
    srcs = [
        "audio_pipeline.h",
        "audio_pipeline.cc",
        "alsa_output.h",
        "alsa_output.cc",
        "main_linux.cc",
    ],
    deps = [
        "//keebird/src/ui:ui",
        "//keebird/src/util:queues",
        "//keebird/src/synth:synth"
    ],
    visibility = [
        "//visibility:public"
    ],
    linkopts = [
        "-lasound",
        "-pthread"
    ]
)

cc_binary(
    name = "keebird_linux",
    srcs = [
        "adsr_envelope.h",
        "adsr_envelope.cc",
        "audio_pipeline.h",
        "audio_pipeline.cc",
        "alsa_output.h",
        "alsa_output.cc",
        "main_linux.cc",
        "mixer.h",
        "note.h",
        "note.cc",
        "osc.h",
        "osc.cc",
    ],
    deps = [
        "//keebird/src/ui:ui",
        "//keebird/src/util:queues"
    ],
    visibility = [
        "//visibility:public"
    ],
    linkopts = [
        "-lasound",
        "-pthread"
    ]
)

cc_binary(
    name = "nome_linux",
    srcs = [
        "src/adsr_envelope.h",
        "src/adsr_envelope.cc",
        "src/alsa_output.h",
        "src/alsa_output.cc",
        "src/beat.h",
        "src/beat.cc",
        "src/mixer.h",
        "src/settings.h",
        "src/settings.cc",
        "src/osc.h",
        "src/osc.cc",
        "src/main_linux.cc"
    ],
    linkopts = [
        "-lasound"
    ]
)

cc_binary(
    name = "nome_stm32",
    srcs = [
        "src/startup_stm32f411xe.s",
        "src/stm32f4xx_it.h",
        "src/stm32f4xx_it.cc",
        "src/system_stm32f4xx.cc",
        "src/adsr_envelope.h",
        "src/adsr_envelope.cc",
        "src/beat.h",
        "src/beat.cc",
        "src/mixer.h",
        "src/pinout.h",
        "src/pinout.cc",
        "src/settings.h",
        "src/settings.cc",
        "src/user_interface.h",
        "src/user_interface.cc",
        "src/osc.h",
        "src/osc.cc",
        "src/main_stm32.cc",
    ],
    copts = [
        "-fno-rtti",
        "-specs=nosys.specs"
    ] + select({
        "//third_party/STM/stm32f4:target_stm32f411": [
            "-DSTM32F411xE",
            "-DTARGET_BREADBOARD"
        ],
        "//third_party/STM/stm32f4:target_stm32f413": [
            "-DSTM32F413_423xx",
            "-DTARGET_PROTOTYPE"
        ]
    }),
    linkopts = select({
        "//third_party/STM/stm32f4:target_stm32f411": [
            "-Tnome/linker_scripts/STM32F411RETx_FLASH.ld"
        ],
        "//third_party/STM/stm32f4:target_stm32f413": [
            "-Tnome/linker_scripts/STM32F413CGUx_FLASH.ld"
        ]
    }),
    deps = [
        "//drivers/stm32:gpio_common",
        "//drivers/stm32:i2c_common",
        "//drivers/stm32:i2s_common",
        "//drivers/stm32:cs43l22_dac",
        "//drivers/stm32:pec11_encoder",
        "//drivers/stm32:status_led"
    ] + select({
        "//third_party/STM/stm32f4:target_stm32f411": [
            "linker_scripts/STM32F411RETx_FLASH.ld",
            "//drivers/stm32:ht16K33_display"
        ],
        "//third_party/STM/stm32f4:target_stm32f413": [
            "linker_scripts/STM32F413CGUx_FLASH.ld",
            "//drivers/stm32:as1115_display"
        ]
    }),
    linkstatic = 1
)

load("//tools/arm_compiler:raw_binary.bzl", "hex_binary")

hex_binary(
    name = "nome",
    src = ":nome_stm32"
)


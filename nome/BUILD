cc_binary(
    name = "nome_bin",
    srcs = [
        "src/startup_stm32f411xe.s",
        "src/stm32f4xx_it.h",
        "src/stm32f4xx_it.cc",
        "src/system_stm32f4xx.cc",
        "src/adsr_envelope.h",
        "src/adsr_envelope.cc",
        "src/beat.h",
        "src/beat.cc",
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
        ":target_breadboard": [
            "-DSTM32F411xE",
            "-DTARGET_BREADBOARD"
        ],
        ":target_prototype": [
            "-DSTM32F413_423xx",
            "-DTARGET_PROTOTYPE"
        ]
    }),
    linkopts = select({
        ":target_breadboard": ["-Tnome/linker_scripts/STM32F411RETx_FLASH.ld"],
        ":target_prototype": ["-Tnome/linker_scripts/STM32F413CGUx_FLASH.ld"]
    }),
    deps = [
        "//third_party/STM:stm_cmsis",
        "//drivers/stm32:protocol_common",
        "//drivers/stm32:as1115_display",
        "//drivers/stm32:cs43l22_dac",
        "//drivers/stm32:ht16K33_display",
        "//drivers/stm32:pec11_encoder",
        "//drivers/stm32:status_led"
    ] + select({
        ":target_breadboard": ["linker_scripts/STM32F411RETx_FLASH.ld"],
        ":target_prototype": ["linker_scripts/STM32F413CGUx_FLASH.ld"]
    }),
    linkstatic = 1
)

load("//tools/arm_compiler:raw_binary.bzl", "hex_binary")

hex_binary(
    name = "nome",
    src = ":nome_bin"
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

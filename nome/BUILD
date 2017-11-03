COMMON_SOURCES = [
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
]

COMMON_COPTS = [
    "-fno-rtti",
    "-specs=nosys.specs",
]

cc_binary(
    name = "nome_breadboard_bin",
    srcs = COMMON_SOURCES,
    copts = COMMON_COPTS + [
        "-DSTM32F411xE",
        "-DTARGET_BREADBOARD"
    ],
    linkopts = ["-Tnome/linker_scripts/STM32F411RETx_FLASH.ld"],
    deps = [
        "//third_party/STM:stm_cmsis",
        "//stm32_drivers:stm32_drivers_breadboard",
        "linker_scripts/STM32F411RETx_FLASH.ld",
    ],
    linkstatic = 1
)

cc_binary(
    name = "nome_prototype_bin",
    srcs = COMMON_SOURCES,
    copts = COMMON_COPTS + [
        "-DSTM32F413_423xx",
        "-DTARGET_PROTOTYPE"
    ],
    linkopts = ["-Tnome/linker_scripts/STM32F413CGUx_FLASH.ld"],
    deps = [
        "//third_party/STM:stm_cmsis",
        "//stm32_drivers:stm32_drivers_prototype",
        "linker_scripts/STM32F413CGUx_FLASH.ld"
    ],
    linkstatic = 1
)

load("//tools/arm_compiler:raw_binary.bzl", "hex_binary")

hex_binary(
    name = "nome_breadboard",
    src = ":nome_breadboard_bin"
)

hex_binary(
    name = "nome_prototype",
    src = ":nome_prototype_bin"
)

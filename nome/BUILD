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
        "-Ithird_party/STM/STM32F4xx_StdPeriph_Driver/inc",
        "-Ithird_party/STM/CMSIS/Include",
        "-Ithird_party/STM/CMSIS/Device/ST/STM32F4xx/Include",
        "-Idrivers/src",
        "-Inome/src",
        "-specs=nosys.specs",
        "-DSTM32F411xE",
        "-DTARGET_BREADBOARD"
    ],
    linkopts = ["-Tnome/src/STM32F411RETx_FLASH.ld"],
    deps = [
        "//third_party/STM/CMSIS:stm_cmsis",
        "//drivers:stm_drivers",
        "src/STM32F411RETx_FLASH.ld",
    ],
    linkstatic = 1
)

load("//tools/arm_compiler:raw_binary.bzl", "hex_binary")

hex_binary(
    name = "nome",
    src = ":nome_bin"
)

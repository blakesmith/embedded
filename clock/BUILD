cc_binary(
    name = "clock_stm32",
    srcs = [
        "src/startup_stm32l1xx_md.s",
        "src/system_stm32l1xx.h",
        "src/system_stm32l1xx.cc",
        "src/main.cc",
    ],
    copts = [
        "-fno-rtti",
        "-specs=nosys.specs",
        "-DSTM32L1XX_MD"
    ],
    linkopts = [
        "-Tclock/linker_scripts/STM32L151C8_FLASH.ld"
    ],
    deps = [
        "//drivers/stm32:rtc",
        "linker_scripts/STM32L151C8_FLASH.ld"
    ],
    linkstatic = 1
)

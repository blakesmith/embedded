cc_binary(
    name = "clock_stm32",
    srcs = [
        "src/main.cc",
        "src/ui.h",
        "src/ui.cc",
    ],
    copts = select({
        "//third_party/STM/stm32f4:target_stm32f411": [
            "-DSTM32F411xE",
        ],
        "//third_party/STM/stm32l1:target_stm32l1": [
            "-DSTM32L1XX_MD"
        ]
    }) + [
        "-fno-rtti",
        "-specs=nosys.specs",
        "-Og",
        "-g"
    ],
    linkopts = select({
        "//third_party/STM/stm32f4:target_stm32f411": [
            "-Tthird_party/STM/stm32f4/STM32F411RETx_FLASH.ld"
        ],
        "//third_party/STM/stm32l1:target_stm32l1": [
            "-Tthird_party/STM/stm32l1/STM32L151C8_FLASH.ld"
        ]
    }),
    deps = select({
        "//third_party/STM/stm32f4:target_stm32f411": [
            "//third_party/STM/stm32f4:bin_common",
            "//third_party/STM/stm32f4:stm32f411_linker_script",
        ],
        "//third_party/STM/stm32l1:target_stm32l1": [
            "//third_party/STM/stm32l1:bin_common",
            "//third_party/STM/stm32l1:stm32l151_linker_script",
        ]
    }) + [
        "//drivers/stm32:gpio_common",
        "//drivers/stm32:i2c_common",
        "//drivers/stm32:rtc",
        "//drivers/stm32:as1115_display",
        "//drivers/stm32:pec11_encoder",
        "//drivers/stm32:status_led",
    ],
    linkstatic = 1
)

load("//tools/arm_compiler:raw_binary.bzl", "hex_binary")

hex_binary(
    name = "clock",
    src = ":clock_stm32"
)

filegroup(
    name = "clock_flash_artifact",
    srcs = [
        ":clock"
    ],
    visibility = [
        "//visibility:public"
    ]
)

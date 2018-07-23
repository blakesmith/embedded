cc_binary(
    name = "keebee_stm32",
    srcs = [
        "src/main.cc",
        "src/layout.h",
        "src/layout.cc",
        "src/key_pipeline.h",
        "src/key_pipeline.cc",
        "src/stm32f0xx_it.cc",
        "src/stm32f0xx_it.h",
        "src/usb_keyboard.h",
        "src/usb_keyboard.cc",
    ],
    copts = [
        "-DSTM32F042x6",
        "-fno-rtti",
        "-specs=nosys.specs"
    ],
    linkopts = [
        "-Tthird_party/STM/stm32f0/STM32F042K6Tx_FLASH.ld"
    ],
    deps = [
        "//drivers/stm32:scan_matrix",
        "//drivers/stm32:status_led",
        "//drivers/stm32:gpio_common",
        "//third_party/STM/stm32f0/common:common_bin",
        "//third_party/STM/stm32f0/cube:base",
        "//third_party/STM/stm32f0:stm32f042_linker_script",
        "//keebee/src/hid:keyboard"
    ],
    linkstatic = 1
)

load("//tools/arm_compiler:raw_binary.bzl", "hex_binary")

hex_binary(
    name = "keebee",
    src = ":keebee_stm32"
)

filegroup(
    name = "keebee_flash_artifact",
    srcs = [
        ":keebee"
    ],
    visibility = [
        "//visibility:public"
    ]
)

load("//tools/scripts:openocd.bzl", "openocd_flash")

openocd_flash(
    name = "keebee_flash",
    src = "//tools/scripts:openocd_board_flash.sh",
    artifact = ":keebee_flash_artifact",
    target = "/usr/share/openocd/scripts/board/st_nucleo_f0.cfg"
)



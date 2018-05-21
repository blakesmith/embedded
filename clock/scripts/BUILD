sh_binary(
    name = "discovery_flash",
    srcs = [
        "discovery_flash.sh"
    ],
    data = [
        "//clock:clock_flash_artifact"
    ],
    args = [
        "/usr/share/openocd/scripts/board/stm32f4discovery.cfg",
        "$(location //clock:clock_flash_artifact)"
    ]
)

sh_binary(
    name = "breakout_flash",
    srcs = [
        "breakout_flash.sh"
    ],
    data = [
        "//clock:clock_flash_artifact"
    ],
    args = [
        "/usr/share/openocd/scripts/target/stm32l1.cfg",
        "$(location //clock:clock_flash_artifact)"
    ]
)

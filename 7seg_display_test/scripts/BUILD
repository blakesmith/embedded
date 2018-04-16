sh_binary(
    name = "discovery_flash",
    srcs = [
        "discovery_flash.sh"
    ],
    data = [
        "//7seg_display_test:test_flash_artifact"
    ],
    args = [
        "/usr/share/openocd/scripts/board/stm32f4discovery.cfg",
        "$(location //7seg_display_test:test_flash_artifact)"
    ]
)

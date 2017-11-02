def arm_none_repository(arch="linux"):
    if arch == "linux":
        native.new_http_archive(
            name = "com_arm_developer_toolchain_gcc_6_2",
            build_file = str(Label("//compilers:arm_none_gcc_6.2.BUILD")),
            strip_prefix = "gcc-arm-none-eabi-6-2017-q1-update",
            url = "https://developer.arm.com/-/media/Files/downloads/gnu-rm/6_1-2017q1/gcc-arm-none-eabi-6-2017-q1-update-linux.tar.bz2"
            #url = "https://developer.arm.com/-/media/Files/downloads/gnu-rm/6-2016q4/gcc-arm-none-eabi-6_2-2016q4-20161216-linux.tar.bz2"
        )
    if arch == "mac":
        native.new_http_archive(
            name = "com_arm_developer_toolchain_gcc_6_2",
            build_file = str(Label("//compilers:arm_none_gcc_6.2.BUILD")),
            strip_prefix = "gcc-arm-none-eabi-6_2-2016q4",
            url = "https://developer.arm.com/-/media/Files/downloads/gnu-rm/6-2016q4/gcc-arm-none-eabi-6_2-2016q4-20161216-mac.tar.bz2"
        )


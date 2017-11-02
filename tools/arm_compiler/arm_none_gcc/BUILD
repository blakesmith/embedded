package(default_visibility = ["//tools/arm_compiler:__pkg__"])

filegroup(
    name = "srcs",
    srcs = glob(["**"]),
    visibility = ["//tools/arm_compiler:__pkg__"],
)

filegroup(
    name = "gcc",
    srcs = [
        "arm-none-eabi-gcc",
        "@com_arm_developer_toolchain_gcc_6_2//:gcc",
    ],
)

filegroup(
    name = "ar",
    srcs = [
        "arm-none-eabi-ar",
        "@com_arm_developer_toolchain_gcc_6_2//:ar",
    ],
)

filegroup(
    name = "ld",
    srcs = [
        "arm-none-eabi-ld",
        "@com_arm_developer_toolchain_gcc_6_2//:ld",
    ],
)

filegroup(
    name = "nm",
    srcs = [
        "arm-none-eabi-nm",
        "@com_arm_developer_toolchain_gcc_6_2//:nm",
    ],
)

filegroup(
    name = "objcopy",
    srcs = [
        "arm-none-eabi-objcopy",
        "@com_arm_developer_toolchain_gcc_6_2//:objcopy",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "objdump",
    srcs = [
        "arm-none-eabi-objdump",
        "@com_arm_developer_toolchain_gcc_6_2//:objdump",
    ],
)

filegroup(
    name = "strip",
    srcs = [
        "arm-none-eabi-strip",
        "@com_arm_developer_toolchain_gcc_6_2//:strip",
    ],
)

filegroup(
    name = "as",
    srcs = [
        "arm-none-eabi-as",
        "@com_arm_developer_toolchain_gcc_6_2//:as",
    ],
)

filegroup(
    name = "tool-wrappers",
    srcs = [
        ":ar",
        ":as",
        ":gcc",
        ":ld",
        ":nm",
        ":objcopy",
        ":objdump",
        ":strip",
    ],
)

# This is the entry point for --crosstool_top.  Toolchains are found
# by lopping off the name of --crosstool_top and searching for
# 'cc-compiler-${CPU}' in this BUILD file, where CPU is the target CPU
# specified in --cpu.
#
# This file group should include
#   * all cc_toolchain targets supported
#   * all file groups that said cc_toolchain might refer to,
# including the default_grte_top setting in the CROSSTOOL
# protobuf.
package(default_visibility = ["//visibility:public"])

filegroup(
    name = "toolchain_fg",
    srcs = [
        ":cc-compiler-armeabi-v7a",
        ":cc-compiler-k8",
        ":arm_none_all_files",
        "@com_arm_developer_toolchain_gcc_6_2//:compiler_components",
    ],
)

filegroup(
    name = "srcs",
    srcs = glob(["**"]) + [
        "//tools/arm_compiler/arm_none_gcc:srcs",
    ],
    visibility = ["//tools/arm_compiler:__pkg__"],
)

cc_toolchain_suite(
    name = "toolchain",
    # target_cpu | compiler
    toolchains = {
        "armeabi-v7a|gcc": "cc-compiler-armeabi-v7a",
        "k8|compiler": "cc-compiler-k8",
    },
)

filegroup(
    name = "arm_none_all_files",
    srcs = [
        "//tools/arm_compiler/arm_none_gcc:tool-wrappers",
        "@com_arm_developer_toolchain_gcc_6_2//:compiler_pieces",
    ],
)

filegroup(
    name = "arm_none_linker_files",
    srcs = [
        "//tools/arm_compiler/arm_none_gcc:ar",
        "//tools/arm_compiler/arm_none_gcc:gcc",
        "//tools/arm_compiler/arm_none_gcc:ld",
        "//tools/arm_compiler/arm_none_gcc:objcopy", 
        "@com_arm_developer_toolchain_gcc_6_2//:compiler_pieces",
    ],
)

filegroup(
    name = "arm_none_compiler_files",
    srcs = [
        "//tools/arm_compiler/arm_none_gcc:as",
        "//tools/arm_compiler/arm_none_gcc:gcc",
        "//tools/arm_compiler/arm_none_gcc:ld",
        "//tools/arm_compiler/arm_none_gcc:objcopy", 
    ],
)

filegroup(
    name = "empty",
    srcs = [],
)

cc_toolchain(
    name = "cc-compiler-armeabi-v7a",
    all_files = ":arm_none_all_files",
    compiler_files = ":arm_none_compiler_files",
    cpu = "armeabi-v7a",
    dwp_files = ":empty",
    dynamic_runtime_libs = [":empty"],
    linker_files = ":arm_none_linker_files",
    objcopy_files = "//tools/arm_compiler/arm_none_gcc:objcopy",
    static_runtime_libs = [":empty"],
    strip_files = "//tools/arm_compiler/arm_none_gcc:strip",
    supports_param_files = 1,
    visibility = ["//visibility:public"],
)

cc_toolchain(
    name = "cc-compiler-k8",
    all_files = ":empty",
    compiler_files = ":empty",
    cpu = "local",
    dwp_files = ":empty",
    dynamic_runtime_libs = [":empty"],
    linker_files = ":empty",
    objcopy_files = ":empty",
    static_runtime_libs = [":empty"],
    strip_files = ":empty",
    supports_param_files = 1,
)

def _bin_impl(ctx):
    output = ctx.outputs.out
    input = ctx.file.src
    objcopy = ctx.fragments.cpp.objcopy_executable

    ctx.action(
        inputs=[input] + ctx.files._objcopy,
        outputs=[output],
        progress_message="Creating raw binary from %s" % input.short_path,
        executable = objcopy,
        arguments = [
            "-O",
            "binary",
            "-S",
            input.path,
            output.path
        ])

raw_binary = rule(
    implementation=_bin_impl,
    fragments=["cpp"],
    attrs={
        "src": attr.label(mandatory=True, allow_files=True, single_file=True),
        "_objcopy": attr.label(default=Label("//tools/arm_compiler/arm_none_gcc:objcopy"), allow_files=True)
    },
    outputs={"out": "%{name}.bin"},
)

def _hex_impl(ctx):
    output = ctx.outputs.out
    input = ctx.file.src
    objcopy = ctx.fragments.cpp.objcopy_executable

    ctx.action(
        inputs=[input] + ctx.files._objcopy,
        outputs=[output],
        progress_message="Creating hex from %s" % input.short_path,
        executable = objcopy,
        arguments = [
            "-O",
            "ihex",
            input.path,
            output.path
        ])

hex_binary = rule(
    implementation=_hex_impl,
    fragments=["cpp"],
    attrs={
        "src": attr.label(mandatory=True, allow_files=True, single_file=True),
        "_objcopy": attr.label(default=Label("//tools/arm_compiler/arm_none_gcc:objcopy"), allow_files=True)
    },
    outputs={"out": "%{name}.hex"},
)
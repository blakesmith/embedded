def openocd_flash(name, artifact, target):
    native.sh_binary(
        name = name,
        srcs = [
            "//tools/scripts:openocd_flash.sh"
        ],
        data = [
            artifact
        ],
        args = [
            target,
            "$(location {})".format(artifact)
        ]
    )

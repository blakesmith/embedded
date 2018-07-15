def openocd_flash(name, artifact, target, src="//tools/scripts:openocd_flash.sh"):
    native.sh_binary(
        name = name,
        srcs = [src],
        data = [
            artifact
        ],
        args = [
            target,
            "$(location {})".format(artifact)
        ]
    )

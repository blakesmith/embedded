URLS = {
    "mac os x": ("cb52433610d0084ee85abcd1ac4879303acba0b6a4ecfe5a5113c09f0ee265f0",
                 "gcc-arm-none-eabi-6_2-2016q4",
                 "https://developer.arm.com/-/media/Files/downloads/gnu-rm/6-2016q4/gcc-arm-none-eabi-6_2-2016q4-20161216-mac.tar.bz2"),
    "linux": ("e7aad2579f02e3b095c6d7899ca5e6a70cfa9b8a8cbd6abd868da849d416c2eb",
              "gcc-arm-none-eabi-6-2017-q1-update",
              "https://developer.arm.com/-/media/Files/downloads/gnu-rm/6_1-2017q1/gcc-arm-none-eabi-6-2017-q1-update-linux.tar.bz2")
}

def _arm_none_repository_impl(ctx):
    value = URLS[ctx.os.name]
    if not value:
        fail("Unsupported operating system: {}".format(ctx.os.name))
    sha256, strip_prefix, url = value;

    ctx.download_and_extract(
        url=url,
        sha256=sha256,
        stripPrefix=strip_prefix
    )

    ctx.template(
        "BUILD",
        Label("//compilers:arm_none_gcc_6.2.BUILD"),
        substitutions={},
        executable=False
    )

arm_none_repository = repository_rule(_arm_none_repository_impl)

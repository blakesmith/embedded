package(default_visibility = ['//visibility:public'])

filegroup(
  name = 'gcc',
  srcs = [
    'bin/arm-none-eabi-gcc',
  ],
)

filegroup(
  name = 'ar',
  srcs = [
    'bin/arm-none-eabi-ar',
  ],
)

filegroup(
  name = 'ld',
  srcs = [
    'bin/arm-none-eabi-ld',
  ],
)

filegroup(
  name = 'nm',
  srcs = [
    'bin/arm-none-eabi-nm',
  ],
)

filegroup(
  name = 'objcopy',
  srcs = [
    'bin/arm-none-eabi-objcopy',
  ],
)

filegroup(
  name = 'objdump',
  srcs = [
    'bin/arm-none-eabi-objdump',
  ],
)

filegroup(
  name = 'strip',
  srcs = [
    'bin/arm-none-eabi-strip',
  ],
)

filegroup(
  name = 'as',
  srcs = [
    'bin/arm-none-eabi-as',
  ],
)

filegroup(
  name = 'compiler_pieces',
  srcs = glob([
    'arm-none-eabi/**',
    'libexec/**',
    'lib/gcc/arm-none-eabi/**',
    'include/**',
  ]),
)

filegroup(
  name = 'compiler_components',
  srcs = [
    ':gcc',
    ':ar',
    ':ld',
    ':nm',
    ':objcopy',
    ':objdump',
    ':strip',
    ':as',
  ],
)

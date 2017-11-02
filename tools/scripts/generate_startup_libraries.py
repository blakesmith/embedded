#!/usr/bin/env python
from os import listdir
from os.path import isfile, join
import argparse

TEMPLATE = """
cc_library(
    name = "%s_startup",
    srcs = [
        "gcc/%s",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"]
)
"""


def get_files_list(path):
	onlyfiles = [f for f in listdir(path) if isfile(join(path, f))]
	return onlyfiles


def build_templates(path):
	files = get_files_list(path)
	result = []
	for f in files:
		name = f.split('.')[0]
		processor_name = name.split('_')[1]
		print("\"%s\"," % processor_name.upper())
		result.append(TEMPLATE % (processor_name, f))
	return "\n".join(result)

def main():
	parser = argparse.ArgumentParser(prog='generate_startup_libraries')
	parser.add_argument('path', nargs='?',
                        help='s files path')
	args = parser.parse_args()

	if args.path:
		print build_templates(args.path)



if __name__ == '__main__':
    main()
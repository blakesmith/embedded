all: oxidized_flash

setup:
	cargo install cargo-binutils
	rustup target add thumbv7em-none-eabihf
	rustup component add llvm-tools-preview

oxidized_flash:
	cargo build --target thumbv7em-none-eabihf
	cargo readobj --target thumbv7em-none-eabihf --bin oxidized_flash -- --file-headers

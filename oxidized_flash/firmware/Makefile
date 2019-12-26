all: debug_hex

clean:
	rm -rf target

setup:
	cargo install cargo-binutils
	rustup target add thumbv7em-none-eabihf
	rustup component add llvm-tools-preview

debug_build:
	cargo build --target thumbv7em-none-eabihf

debug_hex:
	cargo objcopy --target thumbv7em-none-eabihf --bin oxidized_flash -- -O ihex target/thumbv7em-none-eabihf/debug/oxidized_flash.hex

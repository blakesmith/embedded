all: debug_binary

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

debug_binary: debug_build
	cargo objcopy --target thumbv7em-none-eabihf --bin oxidized_flash -- -O binary target/thumbv7em-none-eabihf/debug/oxidized_flash.bin

debug_flash: debug_hex
	./openocd_flash.sh /usr/local/share/openocd/scripts/target/atsame5x.cfg target/thumbv7em-none-eabihf/debug/oxidized_flash.hex

release_build:
	cargo build --target thumbv7em-none-eabihf --release

release_hex:
	cargo objcopy --target thumbv7em-none-eabihf --bin oxidized_flash --release -- -O ihex target/thumbv7em-none-eabihf/release/oxidized_flash.hex

release_flash: release_hex
	./openocd_flash.sh /usr/local/share/openocd/scripts/target/atsame5x.cfg target/thumbv7em-none-eabihf/release/oxidized_flash.hex

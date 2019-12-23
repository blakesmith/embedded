#![no_std]
#![no_main]
#![deny(unsafe_code)]

extern crate panic_halt;

use cortex_m_rt::entry;

#[entry]
fn main() -> ! {
    let _y;
    let x = 42;
    _y = x;

    loop {}
}

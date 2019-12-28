#![no_std]
#![no_main]
#![deny(unsafe_code)]

extern crate panic_halt;

extern crate atsamd_hal as hal;

use cortex_m_rt::entry;

use hal::clock::GenericClockController;
use hal::delay::Delay;
use hal::gpio::{Floating, GpioExt, Input, Port};
use hal::prelude::*;
use hal::target_device as pac;
use hal::*;

define_pins!(
    struct Pins,
    target_device: target_device,

    pin ok_led = a20,
    pin button_switch = a21,
);

#[entry]
fn main() -> ! {
    let mut peripherals = pac::Peripherals::take().unwrap();
    let core = pac::CorePeripherals::take().unwrap();
    let mut clocks = GenericClockController::with_internal_32kosc(
        peripherals.GCLK,
        &mut peripherals.MCLK,
        &mut peripherals.OSC32KCTRL,
        &mut peripherals.OSCCTRL,
        &mut peripherals.NVMCTRL,
    );
    let mut pins = Pins::new(peripherals.PORT);
    let mut ok_led = pins.ok_led.into_open_drain_output(&mut pins.port);
    let mut delay = Delay::new(core.SYST, &mut clocks);

    loop {
        delay.delay_ms(200u8);
        ok_led.set_high().unwrap();
        delay.delay_ms(200u8);
        ok_led.set_low().unwrap();
    }
}

#![no_std]
#![no_main]

extern crate panic_halt;

extern crate atsamd_hal as hal;

mod hid;
#[allow(dead_code)]
mod qspi;

use cortex_m::peripheral::NVIC;
use cortex_m_rt::entry;
use cortex_m::interrupt::free as disable_interrupts;

use hal::clock::GenericClockController;
use hal::dbgprint;
use hal::delay::Delay;
use hal::gpio::{Floating, GpioExt, Input, IntoFunction, OpenDrain, Output, Port, PullUp};
use hal::prelude::*;
use hal::sercom::{PadPin, SPIMaster2};
use hal::target_device as pac;
use hal::time::KiloHertz;
use hal::usb::usb_device::bus::UsbBusAllocator;
use hal::usb::usb_device::prelude::{UsbDevice, UsbDeviceBuilder, UsbVidPid};
use hal::usb::UsbBus;
use hal::*;

use pac::gclk::genctrl::SRC_A;
use pac::gclk::pchctrl::GEN_A;
use pac::interrupt;

use crate::hid::{Key, MediaKey, KeyboardHidClass};

// Vendored for now
use crate::qspi::{Command, Qspi};

use apa102_spi::{Apa102, PixelOrder};
use smart_leds::SmartLedsWrite;
use smart_leds_trait::RGB8;

static mut USB_ALLOCATOR: Option<UsbBusAllocator<UsbBus>> = None;
static mut USB_DEV: Option<UsbDevice<UsbBus>> = None;
static mut USB_KEYBOARD: Option<KeyboardHidClass<UsbBus>> = None;

define_pins!(
    struct Pins,
    target_device: target_device,

    pin ok_led = a20,
    pin button_switch = a21,

    // APA102 LEDs
    pin apa_di = a12,
    pin apa_ci = a13,
    // Need a NC, since we don't get any data back from the APA102s
    pin apa_nc = a14,

    //QSPI
    pin flash_sck = b10,
    pin flash_cs = b11,
    pin flash_d0 = a8,
    pin flash_d1 = a9,
    pin flash_d2 = a10,
    pin flash_d3 = a11,

    // USB
    pin usb_dp = a25,
    pin usb_dm = a24,
);

struct Devices {
    pub ok_led: gpio::Pa20<Output<OpenDrain>>,
    pub button_switch: gpio::Pa21<Input<PullUp>>,
    pub apa102: Apa102<
        SPIMaster2<
            hal::sercom::Sercom2Pad2<gpio::Pa14<gpio::PfC>>,
            hal::sercom::Sercom2Pad0<gpio::Pa12<gpio::PfC>>,
            hal::sercom::Sercom2Pad1<gpio::Pa13<gpio::PfC>>,
        >,
    >,
    pub delay: Delay,
    pub flash: Qspi,
}

impl Devices {
    fn setup() -> Devices {
        let mut peripherals = pac::Peripherals::take().unwrap();
        let mut core = pac::CorePeripherals::take().unwrap();
        let mut clocks = GenericClockController::with_internal_32kosc(
            peripherals.GCLK,
            &mut peripherals.MCLK,
            &mut peripherals.OSC32KCTRL,
            &mut peripherals.OSCCTRL,
            &mut peripherals.NVMCTRL,
        );
        let mut pins = Pins::new(peripherals.PORT);
        let ok_led = pins.ok_led.into_open_drain_output(&mut pins.port);
        let button_switch = pins.button_switch.into_pull_up_input(&mut pins.port);

        let apa_di = pins.apa_di.into_push_pull_output(&mut pins.port);
        let apa_ci = pins.apa_ci.into_push_pull_output(&mut pins.port);
        let apa_nc = pins.apa_nc.into_pull_up_input(&mut pins.port);
        let gclk0 = clocks.gclk0();
        let spi: SPIMaster2<
            hal::sercom::Sercom2Pad2<gpio::Pa14<gpio::PfC>>,
            hal::sercom::Sercom2Pad0<gpio::Pa12<gpio::PfC>>,
            hal::sercom::Sercom2Pad1<gpio::Pa13<gpio::PfC>>,
        > = SPIMaster2::new(
            &clocks.sercom2_core(&gclk0).unwrap(),
            KiloHertz(5),
            hal::hal::spi::Mode {
                phase: hal::hal::spi::Phase::CaptureOnFirstTransition,
                polarity: hal::hal::spi::Polarity::IdleLow,
            },
            peripherals.SERCOM2,
            &mut peripherals.MCLK,
            (
                apa_nc.into_pad(&mut pins.port),
                apa_di.into_pad(&mut pins.port),
                apa_ci.into_pad(&mut pins.port),
            ),
        );
        let apa102 = Apa102::new_with_options(spi, 4, true, PixelOrder::RBG);
        let flash = Qspi::new(
            &mut peripherals.MCLK,
            &mut pins.port,
            peripherals.QSPI,
            pins.flash_sck,
            pins.flash_cs,
            pins.flash_d0,
            pins.flash_d1,
            pins.flash_d2,
            pins.flash_d3,
        );
        let delay = Delay::new(core.SYST, &mut clocks);

        let usb_gclk = clocks
            .configure_gclk_divider_and_source(GEN_A::GCLK2, 1, SRC_A::DFLL, false)
            .unwrap();
        let usb_clock = &clocks.usb(&usb_gclk).unwrap();
        unsafe {
            let bus_allocator = {
                USB_ALLOCATOR = Some(UsbBusAllocator::new(UsbBus::new(
                    usb_clock,
                    &mut peripherals.MCLK,
                    pins.usb_dm.into_function(&mut pins.port),
                    pins.usb_dp.into_function(&mut pins.port),
                    peripherals.USB,
                )));
                USB_ALLOCATOR.as_ref().unwrap()
            };

            USB_KEYBOARD = Some(KeyboardHidClass::new(&bus_allocator));
            USB_DEV = Some(
                UsbDeviceBuilder::new(&bus_allocator, UsbVidPid(0xb38, 0x0003))
                    .manufacturer("Oxidized")
                    .product("Oxidized Flash")
                    .serial_number("DS")
                    .max_packet_size_0(64)
                    .build(),
            );
        }

        unsafe {
            core.NVIC.set_priority(interrupt::USB_OTHER, 1);
            core.NVIC.set_priority(interrupt::USB_TRCPT0, 1);
            core.NVIC.set_priority(interrupt::USB_TRCPT1, 1);
            NVIC::unmask(interrupt::USB_OTHER);
            NVIC::unmask(interrupt::USB_TRCPT0);
            NVIC::unmask(interrupt::USB_TRCPT1);
        }

        Devices {
            ok_led,
            button_switch,
            apa102,
            delay,
            flash,
        }
    }
}

fn wait_ready(flash: &mut Qspi, status: &mut [u8; 2]) {
    loop {
        flash.read_command(Command::ReadStatus, status);
        if status.get(1).map(|s| s & 0x03) == Some(0) {
            return;
        }
    }
}

#[entry]
fn main() -> ! {
    dbgprint!("Booting!");

    let mut devices = Devices::setup();
    let mut status: [u8; 2] = [0; 2];

    let mut response: [u8; 20] = [0; 20];
    devices.flash.read_command(Command::ReadId, &mut response);
    wait_ready(&mut devices.flash, &mut status);
    // Make sure we got a valid response back: Check that there's something set
    // for the device manufacturer. If the response is zero, it means we got
    // no response. If 255, it means we got an invalid response. Set our indicator LED if success.
    if response.get(19) != Some(&0x0) && response.get(19) != Some(&0xFF) {
        devices.ok_led.set_high().unwrap();
    }

    let db: [u8; 4] = [0xDE, 0xAD, 0xBE, 0xEF];
    let mut deadbeef: [u8; 4] = [0; 4];
    devices.flash.write_command(Command::WriteEnable, &[]);
    wait_ready(&mut devices.flash, &mut status);
    devices.flash.write_command(Command::EraseChip, &[]);
    wait_ready(&mut devices.flash, &mut status);
    // wait_ready(&mut devices.flash, &mut status);
    // devices.flash.write_command(Command::WriteEnable, &[]);
    // wait_ready(&mut devices.flash, &mut status);
    // devices.flash.erase_command(Command::EraseSector, 0x0);
    // wait_ready(&mut devices.flash, &mut status);
    devices.flash.write_command(Command::WriteEnable, &[]);
    devices.flash.write_memory(0x0, &db);
    wait_ready(&mut devices.flash, &mut status);
    devices.flash.read_memory(0x0, &mut deadbeef);
    wait_ready(&mut devices.flash, &mut status);

    let c0: [RGB8; 2] = [RGB8 { r: 0, g: 0, b: 0 }, RGB8 { r: 0, g: 0, b: 0 }];
    devices.apa102.write(c0.iter().cloned()).unwrap();

    if deadbeef == db {
        let success: [RGB8; 2] = [RGB8 { r: 0, g: 0, b: 32 }, RGB8 { r: 0, g: 0, b: 0 }];
        devices.apa102.write(success.iter().cloned()).unwrap();
    }

    while devices.button_switch.is_high().unwrap() {}

    loop {
        let c1: [RGB8; 2] = [RGB8 { r: 0, g: 64, b: 0 }, RGB8 { r: 64, g: 0, b: 0 }];

        disable_interrupts(|_| unsafe {
            USB_KEYBOARD.as_mut().map(|keyboard| {
                if devices.button_switch.is_low().unwrap() {
                    devices.apa102.write(c1.iter().cloned()).unwrap();
                    keyboard.add_media_key(MediaKey::PlayPause);
                } else {
                    devices.apa102.write(c0.iter().cloned()).unwrap();
                    keyboard.reset_report();
                }

                if keyboard.report_has_changed() {
                    keyboard.send_media_report();
                }
            });
        });
    }
}

fn poll_usb() {
    unsafe {
        USB_DEV.as_mut().map(|device| {
            USB_KEYBOARD.as_mut().map(|keyboard| {
                device.poll(&mut [keyboard]);
            });
        });
    }
}

#[interrupt]
fn USB_OTHER() {
    poll_usb();
}

#[interrupt]
fn USB_TRCPT0() {
    poll_usb();
}

#[interrupt]
fn USB_TRCPT1() {
    poll_usb();
}

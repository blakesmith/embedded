use hal::dbgprint;
use usb_device::class_prelude::*;
use usb_device::Result;

pub struct KeyboardHidClass<'a, B: UsbBus> {
    interface: InterfaceNumber,
    endpoint: EndpointIn<'a, B>,
    report: HIDReport,
    buf: [u8; 8],
}

impl<B: UsbBus> KeyboardHidClass<'_, B> {
    pub fn new(alloc: &UsbBusAllocator<B>) -> KeyboardHidClass<'_, B> {
        KeyboardHidClass {
            interface: alloc.interface(),
            endpoint: alloc.interrupt(8, 10),
            report: HIDReport::new(),
            buf: [0u8; 8],
        }
    }

    pub fn add_key(&mut self, key: Key) {
        self.report.add_key(key);
    }

    pub fn send_report(&mut self) {
        if self.report.has_keys() {
            self.report.fill(&mut self.buf);
            let _ = self.endpoint.write(&self.buf);
            self.report.reset();
            self.report.fill(&mut self.buf);
            let _ = self.endpoint.write(&self.buf);
        }
    }
}

const USB_CLASS_HID: u8 = 0x03;
const IF_SUBCLASS_BOOT: u8 = 0x01;
const IF_PROTOCOL_KEYBOARD: u8 = 0x01;

const HID_DESCRIPTOR: u8 = 0x21;
const HID_COUNTRY_CODE: u8 = 0x00;
const HID_REPORT_DESCRIPTOR: u8 = 0x22;
const HID_KEYBOARD_REPORT_DESC_SIZE: u8 = 45;

const USB_DESCRIPTOR_TYPE_HID: u8 = 0x21;
const USB_DESCRIPTOR_TYPE_HIDREPORT: u8 = 0x22;

const USB_HID_DESCRIPTOR: &[u8] = &[
    0x09,
    HID_DESCRIPTOR,
    0x11,
    0x00, // HID class spec release number, bcdHID
    HID_COUNTRY_CODE,
    0x01, // bNumDescriptors
    HID_REPORT_DESCRIPTOR,
    HID_KEYBOARD_REPORT_DESC_SIZE,
    0x00,
];

const USB_HID_REPORT_DESCRIPTOR: &[u8] = &[
    0x05, 0x01, // USAGE_PAGE (Generic Desktop)
    0x09, 0x06, // USAGE (Keyboard)
    0xa1, 0x01, // COLLECTION (Application)
    0x05, 0x07, // USAGE_PAGE (Keyboard)
    0x19, 0xe0, // USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7, // USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0x01, // LOGICAL_MAXIMUM (1)
    0x75, 0x01, // REPORT_SIZE (1)
    0x95, 0x08, // REPORT_COUNT (8)
    0x81, 0x02, // INPUT (Data,Var,Abs) //1 byte
    0x95, 0x01, // REPORT_COUNT (1)
    0x75, 0x08, // REPORT_SIZE (8)
    0x81, 0x03, // INPUT (Cnst,Var,Abs) //1 byte
    0x95, 0x06, // REPORT_COUNT (6)
    0x75, 0x08, // REPORT_SIZE (8)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0x65, // LOGICAL_MAXIMUM (101)
    0x05, 0x07, // USAGE_PAGE (Keyboard)
    0x19, 0x00, // USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65, // USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00, // INPUT (Data,Ary,Abs) //6 bytes
    0xc0, // END_COLLECTION
];

impl<B: UsbBus> UsbClass<B> for KeyboardHidClass<'_, B> {
    fn get_configuration_descriptors(&self, writer: &mut DescriptorWriter) -> Result<()> {
        // Write out interface and endpoint descriptors. Device descriptors
        // are sent when the UsbDevice is created.

        writer.interface(
            self.interface,
            USB_CLASS_HID,
            IF_SUBCLASS_BOOT,
            IF_PROTOCOL_KEYBOARD,
        )?;

        writer.write(
            HID_DESCRIPTOR,
            &[
                0x11,
                0x00, // HID class spec release number, bcdHID
                HID_COUNTRY_CODE,
                0x01, // bNumDescriptors
                HID_REPORT_DESCRIPTOR,
                HID_KEYBOARD_REPORT_DESC_SIZE,
                0x00,
            ],
        )?;

        writer.endpoint(&self.endpoint)?;

        dbgprint!("Done sending descriptors");

        Ok(())
    }

    fn control_in(&mut self, xfer: ControlIn<B>) {
        let req = xfer.request();

        if !(req.recipient == control::Recipient::Interface
            && req.index == u8::from(self.interface) as u16)
        {
            return;
        }

        match req.descriptor_type_index().0 {
            USB_DESCRIPTOR_TYPE_HID => { xfer.accept_with_static(USB_HID_DESCRIPTOR).ok(); }
            USB_DESCRIPTOR_TYPE_HIDREPORT => { xfer.accept_with_static(USB_HID_REPORT_DESCRIPTOR).ok(); }
            _ => {
                xfer.reject().ok();
            }
        }
    }
}

struct HIDReport {
    current_key: usize,
    keys: [u8; 6],
}


// Scan codes taken from: https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2
#[repr(u8)]
#[derive(Copy, Clone, Eq, PartialEq, Debug)]
#[allow(dead_code)]
pub enum Key {
    MediaPlayPause = 0xe8,
    MediaStop = 0xe9,
    MediaPrev = 0xea,
    MediaNext = 0xeb,
    A = 0x04,
}

impl Key {
    pub fn raw(&self) -> u8 {
        *self as u8
    }
}

impl HIDReport {
    pub fn new() -> Self {
        Self {
            current_key: 0,
            keys: [0u8; 6],
        }
    }

    pub fn add_key(&mut self, key: Key) {
        if self.current_key == 5 {
            return;
        }
        self.keys[self.current_key] = key.raw();
        self.current_key = self.current_key + 1;
    }

    pub fn has_keys(&self) -> bool {
        for k in &self.keys {
            if *k != 0 {
                return true;
            }
        }
        return false;
    }

    pub fn reset(&mut self) {
        self.current_key = 0;
        for i in & mut self.keys { *i = 0 }
    }

    pub fn fill(&self, buf: &mut [u8]) {
        buf[0] = 0; // Omit modifiers for now.
        buf[1] = 0; // Gap
        buf[2] = self.keys[0];
        buf[3] = self.keys[1];
        buf[4] = self.keys[2];
        buf[5] = self.keys[3];
        buf[6] = self.keys[4];
        buf[7] = self.keys[5];
    }
}

impl PartialEq for HIDReport {
    fn eq(&self, other: &Self) -> bool {
        self.keys[0] == other.keys[0] &&
            self.keys[1] == other.keys[1] &&
            self.keys[2] == other.keys[2] &&
            self.keys[3] == other.keys[3] &&
            self.keys[4] == other.keys[4] &&
            self.keys[5] == other.keys[5]
    }
}

impl Eq for HIDReport {}

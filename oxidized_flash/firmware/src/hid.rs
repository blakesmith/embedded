use hal::dbgprint;
use usb_device::class_prelude::*;
use usb_device::Result;

pub struct KeyboardHidClass<'a, B: UsbBus> {
    interface: InterfaceNumber,
    endpoint: EndpointIn<'a, B>,
    report: HIDReport,
    buf: [u8; 5],
}

impl<B: UsbBus> KeyboardHidClass<'_, B> {
    pub fn new(alloc: &UsbBusAllocator<B>) -> KeyboardHidClass<'_, B> {
        KeyboardHidClass {
            interface: alloc.interface(),
            endpoint: alloc.interrupt(8, 10),
            report: HIDReport::new(),
            buf: [0u8; 5],
        }
    }

    pub fn add_key(&mut self, key: Key) {
        self.report.add_key(key);
    }

    pub fn add_media_key(&mut self, media_key: MediaKey) {
        self.report.add_media_key(media_key);
    }

    pub fn send_media_report(&mut self) {
        self.report.fill_media(&mut self.buf[0..2]);
        let _ = self.endpoint.write(&self.buf[0..2]);
        self.report.reset();
    }

    pub fn send_key_report(&mut self) {
        self.report.fill_keys(&mut self.buf);
        let _ = self.endpoint.write(&self.buf);
        self.report.reset();
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
    0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
    0x09, 0x06,        // Usage (Keyboard)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x01,        //   Report ID (1)
    0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
    0x75, 0x01,        //   Report Size (1)
    0x95, 0x08,        //   Report Count (8)
    0x19, 0xE0,        //   Usage Minimum (0xE0)
    0x29, 0xE7,        //   Usage Maximum (0xE7)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x01,        //   Logical Maximum (1)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x03,        //   Report Count (3)
    0x75, 0x08,        //   Report Size (8)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x64,        //   Logical Maximum (100)
    0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
    0x19, 0x00,        //   Usage Minimum (0x00)
    0x29, 0x65,        //   Usage Maximum (0x65)
    0x81, 0x00,        //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              // End Collection
    0x05, 0x0C,        // Usage Page (Consumer)
    0x09, 0x01,        // Usage (Consumer Control)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x02,        //   Report ID (2)
    0x05, 0x0C,        //   Usage Page (Consumer)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x01,        //   Logical Maximum (1)
    0x75, 0x01,        //   Report Size (1)
    0x95, 0x07,        //   Report Count (7)
    0x09, 0xB5,        //   Usage (Scan Next Track)
    0x09, 0xB6,        //   Usage (Scan Previous Track)
    0x09, 0xB7,        //   Usage (Stop)
    0x09, 0xB8,        //   Usage (Eject)
    0x09, 0xCD,        //   Usage (Play/Pause)
    0x09, 0xE2,        //   Usage (Mute)
    0x09, 0xE9,        //   Usage (Volume Increment)
    0x09, 0xEA,        //   Usage (Volume Decrement)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              // End Collection
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
    keys: [u8; 3],
    media_keys: u8,
}


// Scan codes taken from: https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
#[repr(u8)]
#[derive(Copy, Clone, Eq, PartialEq, Debug)]
#[allow(dead_code)]
pub enum Key {
    A = 0x04,
}

// See documentation here: https://notes.iopush.net/custom-usb-hid-device-descriptor-media-keyboard/
#[repr(u8)]
#[derive(Copy, Clone, Eq, PartialEq, Debug)]
#[allow(dead_code)]
pub enum MediaKey {
    ScanNext = 0x01,
    ScanPrev = 0x02,
    Stop = 0x04,
    Eject = 0x08,
    PlayPause = 0x10,
    Mute = 0x20,
    VolumeUp = 0x40,
    VolumeDown = 0x80,
}

impl MediaKey {
    pub fn raw(&self) -> u8 {
        *self as u8
    }
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
            keys: [0u8; 3],
            media_keys: 0,
        }
    }

    pub fn add_key(&mut self, key: Key) {
        if self.current_key == 3 {
            return;
        }
        self.keys[self.current_key] = key.raw();
        self.current_key = self.current_key + 1;
    }

    pub fn add_media_key(&mut self, media_key: MediaKey) {
        self.media_keys |= media_key.raw();
    }

    pub fn reset(&mut self) {
        self.current_key = 0;
        self.media_keys = 0;
        for i in &mut self.keys { *i = 0 }
    }

    pub fn fill_media(&self, buf: &mut [u8]) {
        buf[0] = 2; // Report id
        buf[1] = self.media_keys;
    }

    pub fn fill_keys(&self, buf: &mut [u8]) {
        buf[0] = 1; // Report id
        buf[1] = 0; // Omit modifiers for now
        buf[2] = self.keys[0];
        buf[3] = self.keys[1];
        buf[4] = self.keys[2];
    }
}

impl PartialEq for HIDReport {
    fn eq(&self, other: &Self) -> bool {
        self.keys[0] == other.keys[0] &&
            self.keys[1] == other.keys[1] &&
            self.keys[2] == other.keys[2] &&
            self.media_keys == other.media_keys
    }
}

impl Eq for HIDReport {}

use hal::dbgprint;
use usb_device::class_prelude::*;
use usb_device::Result;

pub struct KeyboardHidClass<'a, B: UsbBus> {
    interface: InterfaceNumber,
    endpoint: EndpointIn<'a, B>,
}

impl<B: UsbBus> KeyboardHidClass<'_, B> {
    pub fn new(alloc: &UsbBusAllocator<B>) -> KeyboardHidClass<'_, B> {
        KeyboardHidClass {
            interface: alloc.interface(),
            endpoint: alloc.interrupt(8, 10),
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

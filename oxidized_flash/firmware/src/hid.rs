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

impl<B: UsbBus> UsbClass<B> for KeyboardHidClass<'_, B> {
    fn get_configuration_descriptors(&self, writer: &mut DescriptorWriter) -> Result<()> {
        // Write out interface and endpoint descriptors. Device descriptors
        // are sent elsewhere.
        Ok(())
    }

    fn control_in(&mut self, xfer: ControlIn<B>) {
        let req = xfer.request();

        match req.request {
            // Send HID descriptors
            _ => {}
        }
    }
}

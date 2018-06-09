pcb_height = 58.420;
pcb_length = 45.720;
pcb_thickness = 1.6; // TODO: double check, add tolerance

stand_width = pcb_length + 4;
stand_length = 30.0;
stand_height = 10.0;

usb_height = 2.80;
usb_width = 5.10 + 0.15; // Includes tolerance
usb_length = 7.90 + 0.15; // includes tolerance

usb_cutout_length = usb_length + 5;
usb_cutout_thickness = usb_width + 5;
usb_cutout_depth = 5.0;

pcb_cutout_length = pcb_length;
pcb_cutout_thickness = pcb_thickness; // TODO: Needs to account for the USB connector
pcb_cutout_depth = usb_cutout_depth;

union() {
    stand();
}

module stand() {
    difference() {
        cube([stand_width,
              stand_length,
              stand_height],
             center = true);
        cutout();
    }
}


module cutout() {
    pcb_cutout_x = -(pcb_cutout_length / 2);
    pcb_cutout_y = -(pcb_cutout_thickness / 2);
    pcb_cutout_z = (stand_height / 2) - pcb_cutout_depth + 1;

    usb_cutout_x = -(usb_cutout_length / 2);
    usb_cutout_y = -(usb_cutout_thickness / 2);
    usb_cutout_z = (stand_height / 2) - usb_cutout_depth + 1;

    union() {
        translate([pcb_cutout_x, pcb_cutout_y, pcb_cutout_z])
            cube([pcb_cutout_length,
                  pcb_cutout_thickness,
                  pcb_cutout_depth],
                 cunter = true);
        translate([usb_cutout_x, usb_cutout_y, usb_cutout_z])
            cube([usb_cutout_length,
                  usb_cutout_thickness,
                  usb_cutout_depth],
                 cunter = true);
    }
}

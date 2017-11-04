pcb_length = 91.44;
pcb_width = 91.44;
pcb_height = 1.6;

pcb_tolerance_gap = 3;

enclosure_height = 30;
enclosure_lip_width = 3;
enclosure_width = pcb_width + enclosure_lip_width + pcb_tolerance_gap;
enclosure_length = pcb_length + enclosure_lip_width + pcb_tolerance_gap;

bottom_of_enclosure = ((enclosure_height / 2) - enclosure_lip_width) / -2;

usb_width = 5.5;
usb_length = 7.9;
usb_height = 2.80;
usb_width_offset = 11.68;

headphone_width = 13.50;
headphone_length = 5.60;
headphone_height = 4.60;
headphone_width_offset = -4.57;

encoder_height = 21.5;

battery_width = 34.2;
battery_length = 62.2;
battery_height = 5;

pcb_offset = bottom_of_enclosure + battery_height;
top_of_pcb = pcb_offset + (pcb_height / 2);

battery_offset = bottom_of_enclosure + (battery_height / 2);
headphone_height_offset = top_of_pcb + (headphone_height / 2);
usb_height_offset = top_of_pcb + (usb_height / 2);

union() {
    %bottom_enclosure_piece();
    pcb();
    battery();
}

module battery() {
    translate([0, 0, battery_offset]) {
        color("aqua")
        cube([battery_width,
              battery_length,
              battery_height],
             center=true);
    }
}

module pcb() {
    translate([0, 0, pcb_offset]) {
        color("purple")
            octagon(pcb_width,
                    pcb_length,
                    pcb_height,
                    center=true);
    }
}

module bottom_enclosure_piece() {
    module usb_cutout() {
        translate([enclosure_length / 2,
                   usb_width_offset,
                   usb_height_offset])
            cube([usb_width,
                  usb_length,
                  usb_height],
                 center=true);
    }

    module headphone_cutout() {
        translate([enclosure_length / 2 - headphone_length,
                   headphone_width_offset,
                   headphone_height_offset])
            cube([headphone_width,
                  headphone_length,
                  headphone_height],
                 center=true);
    }
    
    difference() {
        enclosure_piece(true);
        headphone_cutout();
        usb_cutout();
    }
}

module enclosure_piece(center) {
    difference() {
        octagon(enclosure_width,
                enclosure_length,
                enclosure_height / 2,
                center=center);
        translate([0, 0, enclosure_lip_width]) {
            octagon(enclosure_width - enclosure_lip_width,
                    enclosure_length - enclosure_lip_width,
                    (enclosure_height / 2) + enclosure_lip_width,
                    center=center);
        }
    }
}

module octagon(width, length, height, center=false) {
    intersection() {
        cube([width,
              length,
              height], center=center);
        rotate([0, 0, 45]) {
            cube([width,
                  length,
                  height+1], center=center);
        }
    }
}

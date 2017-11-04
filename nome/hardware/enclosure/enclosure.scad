enclosure_height = 25.4;
enclosure_width = 92; 
enclosure_length = 92;
enclosure_lip_width = 3;

encoder_height = 21.5;

union() {
        bottom_enclosure_piece();
}

module bottom_enclosure_piece() {
    module usb_cutout() {
        usb_width = 5.5;
        usb_length = 7.9;
        usb_height = 2.80;

        translate([enclosure_length / 2, 5, 0])
            cube([usb_width,
                  usb_length,
                  usb_height],
                 center=true);
    }

    module headphone_cutout() {
        headphone_width = 13.50;
        headphone_length = 5.60;
        headphone_height = 4.60;

        translate([enclosure_length / 2 - headphone_length, -5, 0])
            cube([headphone_width,
                  headphone_length,
                  headphone_height],
                 center=true);
    }
    
    difference() {
        enclosure_piece(true);
        usb_cutout();
        headphone_cutout();
    }
}

module enclosure_piece(center) {
    difference() {
        hexagon(enclosure_width,
                enclosure_length,
                enclosure_height / 2,
                center=center);
        translate([0, 0, enclosure_lip_width]) {
            hexagon(enclosure_width - enclosure_lip_width,
                    enclosure_length - enclosure_lip_width,
                    enclosure_height / 2,
                    center=center);
        }
    }
}

module hexagon(width, length, height, center=false) {
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

enclosure_height = 25.4;
enclosure_width = 92; 
enclosure_length = 92;
enclosure_lip_width = 3;

union() {
    enclosure_piece(true);
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

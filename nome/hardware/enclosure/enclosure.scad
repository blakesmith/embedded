enclosure_height = 25.4;
enclosure_width = 92; 
enclosure_length = 92;

intersection() {
    cube([enclosure_width,
          enclosure_length,
          enclosure_height / 2], center=true);
    rotate([0, 0, 45]) {
        cube([enclosure_width,
              enclosure_length,
              enclosure_height], center=true);
    }
}

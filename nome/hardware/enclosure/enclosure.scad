pcb_length = 91.44;
pcb_width = 91.44;
pcb_height = 1.6;

pcb_tolerance_gap = 3;

enclosure_height = 45;
enclosure_lip_width = 3;
enclosure_width = pcb_width + enclosure_lip_width + pcb_tolerance_gap;
enclosure_length = pcb_length + enclosure_lip_width + pcb_tolerance_gap;

bottom_of_enclosure = ((enclosure_height / 2) - enclosure_lip_width) / -2;

usb_width = 5.5;
usb_length = 7.9;
usb_height = 2.80;

headphone_width = 13.50;
headphone_length = 5.60;
headphone_height = 4.60;

display_width = 13.3;
display_length = 41.76;
display_height = 7.28;

encoder_width = 13.82;
encoder_length = 13;
encoder_base_height = 6.75;
encoder_shaft_height = 15.591;
encoder_shaft_diameter = 6.0;

switch_width = 9.0;
switch_length = 12.7;
switch_height = 3.5;

battery_width = 34.2;
battery_length = 62.2;
battery_height = 5;

speaker_diameter = 57.5;
speaker_height = 8.7;

pcb_offset = bottom_of_enclosure + battery_height + speaker_height;
top_of_pcb = pcb_offset + (pcb_height / 2);

union() {
    %bottom_enclosure_piece();
    peripherals();
}

module peripherals() {
    union() {
        pcb();
        battery();
        speaker();
        display();
        encoder();
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

    module battery() {
        top_of_speaker = bottom_of_enclosure + speaker_height;
        battery_height_offset = top_of_speaker + (battery_height / 2);
        
        translate([0, 0, battery_height_offset]) {
            color("aqua")
                cube([battery_width,
                      battery_length,
                      battery_height],
                     center=true);
        }
    }

    module speaker() {
        speaker_height_offset = bottom_of_enclosure + (speaker_height / 2);
            
        translate([0, 0, speaker_height_offset]) {
            cylinder(h=speaker_height,
                     d=speaker_diameter,
                     center=true);
        }
    }

    module display() {
        display_height_offset = top_of_pcb + (display_height / 2);

        translate([0, 0, display_height_offset]) {
            color("green")
                rotate(90)
                cube([display_width,
                      display_length,
                      display_height],
                     center=true);
        }
    }

    module encoder() {
        encoder_base_height_offset = top_of_pcb + (encoder_base_height / 2);
        top_of_encoder_base = encoder_base_height_offset + (encoder_base_height / 2);
        encoder_shaft_height_offset = top_of_encoder_base + (encoder_shaft_height / 2);
        encoder_y_offset = (display_width / 2) + (7.1 * 2);

        module encoder_base() {
            translate([0, encoder_y_offset, encoder_base_height_offset]) {
                color("red")
                    rotate(90)
                    cube([encoder_width,
                          encoder_length,
                          encoder_base_height],
                         center=true);
            }
        }

        module encoder_shaft() {
            translate([0, encoder_y_offset, encoder_shaft_height_offset]) {
                color("blue")
                    cylinder(h=encoder_shaft_height,
                             d=encoder_shaft_diameter,
                             center=true);
            }
        }

        encoder_base();
        encoder_shaft();
    }
}

module bottom_enclosure_piece() {
    module usb_cutout() {
        usb_width_offset = 11.68;
        usb_height_offset = top_of_pcb + (usb_height / 2);

        translate([enclosure_length / 2,
                   usb_width_offset,
                   usb_height_offset])
            cube([usb_width,
                  usb_length,
                  usb_height],
                 center=true);
    }

    module headphone_cutout() {
        headphone_height_offset = top_of_pcb + (headphone_height / 2);
        headphone_width_offset = -4.57;

        translate([enclosure_length / 2 - headphone_length,
                   headphone_width_offset,
                   headphone_height_offset])
            cube([headphone_width,
                  headphone_length,
                  headphone_height],
                 center=true);
    }

    module switch_cutout() {
        switch_height_offset = top_of_pcb + (switch_height / 2);
        switch_width_offset = 0;

        translate([-(enclosure_length / 2),
                   switch_width_offset,
                   switch_height_offset])
            cube([switch_width,
                  switch_length,
                  switch_height],
                 center=true);
    }

    module speaker_weave_cutout() {
        speaker_hole_diameter = 2.0;
        speaker_hole_height = enclosure_lip_width * 2;
        speaker_hole_padding = 1.0;

        hole_distance = speaker_hole_diameter + (speaker_hole_padding * 2);
        hole_count = speaker_diameter / hole_distance;

        start_x_offset = -(speaker_diameter / 2);
        start_y_offset = -(speaker_diameter / 2);

        for (x = [0:hole_count]) {
            for (y = [0:hole_count]) {
                translate([start_x_offset + (x * hole_distance),
                           start_y_offset + (y * hole_distance),
                           bottom_of_enclosure - (speaker_hole_height / 2)])
                    cylinder(h=speaker_hole_height,
                             d=speaker_hole_diameter);
            }
        }
    }

    difference() {
        enclosure_piece(true);
        headphone_cutout();
        usb_cutout();
        switch_cutout();
        speaker_weave_cutout();
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

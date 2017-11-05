include <screw_holes.scad>

pcb_length = 91.44;
pcb_width = 91.44;
pcb_height = 1.6;

pcb_tolerance_gap = 3;

enclosure_height = 50;
enclosure_lip_width = 3;
enclosure_width = pcb_width + enclosure_lip_width + pcb_tolerance_gap;
enclosure_length = pcb_length + enclosure_lip_width + pcb_tolerance_gap;

inside_bottom_of_enclosure = ((enclosure_height / 2) - enclosure_lip_width) / -2;
outside_bottom_of_enclosure = (enclosure_height / 2) / -2;

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

mount_post_diameter = 6;
mount_post_radius = mount_post_diameter / 2;
mount_post_tolerance_gap = 2;

pcb_offset = inside_bottom_of_enclosure + battery_height + speaker_height + mount_post_tolerance_gap;
top_of_pcb = pcb_offset + (pcb_height / 2);

union() {
    bottom_enclosure_piece();
    *pcb();
    peripherals();
}

module peripherals() {
    union() {
        battery();
        speaker();
        *display();
        *encoder();
    }

    module battery() {
        top_of_speaker = inside_bottom_of_enclosure + speaker_height;
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
        speaker_height_offset = inside_bottom_of_enclosure + (speaker_height / 2);
            
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

module pcb() {
    translate([0, 0, pcb_offset]) {
        octagon(pcb_width,
                pcb_length,
                pcb_height,
                center=true);
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
        speaker_hole_height = enclosure_lip_width * 2;
        start_x_offset = -(speaker_diameter / 2);
        start_y_offset = -(speaker_diameter / 2);
        start_z_offset = inside_bottom_of_enclosure - (speaker_hole_height / 2);

        module holes() {
            speaker_hole_diameter = 2.0;
            speaker_hole_padding = 1.0;

            hole_distance = speaker_hole_diameter + (speaker_hole_padding * 2);
            hole_count = speaker_diameter / hole_distance;

            for (x = [0:hole_count]) {
                for (y = [0:hole_count]) {
                    translate([start_x_offset + (x * hole_distance),
                               start_y_offset + (y * hole_distance),
                               start_z_offset])
                        cylinder(h=speaker_hole_height,
                                 d=speaker_hole_diameter);
                }
            }
        }
        
        intersection() {
            holes();
            translate([0, 0, start_z_offset])
                cylinder(h=speaker_hole_height,
                         d=speaker_diameter);
        }
    }

    module mount_post(x, y) {
        height = speaker_height + battery_height + (enclosure_lip_width / 2) + mount_post_tolerance_gap;
        z = outside_bottom_of_enclosure + (height / 2);
        difference() {
            %translate([x, y, z])
                cylinder(h=height, d=mount_post_diameter, center=true, $fn=32);
            translate([x, y, 5]) {
                rotate(a=[180, 0, 0]) {
                    screw_hole(DIN965, M3, 10, 7);
                }
            }
        }
    }

    module mount_posts() {
        // Upper left post
        middle_left_corner_x = (pcb_width / 2);
        middle_left_corner_y = (middle_left_corner_x / 2) - mount_post_radius;

        upper_left_x_offset = 7.62;
        upper_left_x = middle_left_corner_x - upper_left_x_offset;
        upper_left_y = middle_left_corner_y;
        mount_post(upper_left_x, -upper_left_y);

        // Upper right post
        middle_right_corner_x = -(pcb_width / 2);
        middle_right_corner_y = (middle_right_corner_x / 2) + mount_post_radius;

        upper_right_x_offset = 7.62;
        upper_right_x = middle_right_corner_x + upper_right_x_offset;
        upper_right_y = middle_right_corner_y;
        mount_post(upper_right_x, upper_right_y);

        // Lower right post
        lower_right_corner_x = -(pcb_width / 2);
        lower_right_corner_y = -((middle_right_corner_x / 2) + mount_post_radius);

        lower_right_x_offset = 5.58;
        lower_right_y_offset = -5.58;
        lower_right_x = lower_right_corner_x + lower_right_x_offset;
        lower_right_y = lower_right_corner_y + lower_right_y_offset;
        mount_post(lower_right_x, lower_right_y);

        // Lower left post
        lower_left_corner_x = (pcb_width / 2);
        lower_left_corner_y = (lower_left_corner_x / 2) - mount_post_radius;

        lower_left_x_offset = -15.24;
        lower_left_y_offset = 5.08;
        lower_left_x = lower_left_corner_x + lower_left_x_offset;
        lower_left_y = lower_left_corner_y + lower_left_y_offset;
        mount_post(lower_left_x, lower_left_y);
    }

    module outer_shell() {
        difference() {
            enclosure_piece(true);
            headphone_cutout();
            usb_cutout();
            switch_cutout();
            speaker_weave_cutout();
        }
    }

    union() {
        *outer_shell();
        mount_posts();
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
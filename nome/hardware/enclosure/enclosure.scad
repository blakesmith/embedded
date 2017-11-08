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
outside_top_of_enclosure = (enclosure_height / 2) / 2;

usb_width = 5.5;
usb_length = 7.9;
usb_height = 2.80;

headphone_width = 13.50;
headphone_length = 5.60;
headphone_height = 4.60;

display_width = 13.3;
display_length = 41.76;
display_height = 7.28;
display_tolerance = 1.5;

encoder_width = 13.82;
encoder_length = 13;
encoder_base_height = 6.75;
encoder_shaft_height = 15.591;
encoder_shaft_diameter = 6.0;
encoder_cutout_tolerance = 1.5;

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

lid_screw_width = 8;
lid_screw_length = 8;
lid_screw_height = 12;

speaker_holder_width = 5;
speaker_holder_length = speaker_diameter / 10;
speaker_holder_height = 3;

pcb_offset = inside_bottom_of_enclosure + battery_height + speaker_height + mount_post_tolerance_gap;
top_of_pcb = pcb_offset + (pcb_height / 2);

union() {
    *nome_logo();
    *outer_enclosure_piece();
    *pcb();
    *peripherals();
    bottom_lid();
}

module nome_logo() {
    height = enclosure_lip_width / 4;
    x = 0;
    y = enclosure_width / 2.5;
    z = enclosure_height / 4;
    translate([x, y, z])
        linear_extrude(height) {
        text("nome",
             halign="center",
             valign="center");
    }
}

module bottom_lid() {
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

    module lid_screw_holes() {
        left_x_offset = (enclosure_width / 2) - (lid_screw_width / 2) - (enclosure_lip_width / 2);
        translate([left_x_offset, 0, inside_bottom_of_enclosure - 2])
            screw_hole(DIN965, M3, 10, 7);

        right_x_offset = -((enclosure_width / 2) - (lid_screw_width / 2) - (enclosure_lip_width / 2));
        translate([right_x_offset, 0, inside_bottom_of_enclosure - 2])
            screw_hole(DIN965, M3, 10, 7);
    }

    module speaker_holder() {
        x = 0;
        y = 0;
        z = 0;
        difference() {
            cube([speaker_holder_width,
                  speaker_holder_length,
                  speaker_holder_height],
                 center=true);
            translate([x - (speaker_holder_width / 2),
                      y,
                      z - (speaker_holder_height / 2)])
                cube([speaker_holder_width,
                      speaker_holder_length + (speaker_holder_length / 10),
                      speaker_holder_height],
                     center=true);
        }
    }

    module speaker_holders() {
        left_x_offset = (speaker_diameter / 2);
        left_z_offset = inside_bottom_of_enclosure + speaker_holder_height;
        translate([left_x_offset,
                   0,
                   left_z_offset])
            speaker_holder();

        right_x_offset = -(speaker_diameter / 2);
        right_z_offset = inside_bottom_of_enclosure + speaker_holder_height;
        translate([right_x_offset,
                   0,
                   right_z_offset])
            rotate([0, 0, 180])
            speaker_holder();
    }

    difference() {
        translate([0, 0, inside_bottom_of_enclosure])
            rounded_octagon(enclosure_width - enclosure_lip_width,
                            enclosure_length - enclosure_lip_width,
                            enclosure_lip_width,
                            center=true);
        speaker_weave_cutout();
        *lid_screw_holes();
    }
    speaker_holders();
}

module peripherals() {
    union() {
        battery();
        speaker();
        display();
        encoder();
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

module outer_enclosure_piece() {
    module display_cutout() {
        display_height_offset = top_of_pcb + display_height;

        translate([0, 0, display_height_offset]) {
            rotate(90)
                cube([display_width + display_tolerance,
                      display_length + display_tolerance,
                      display_height],
                     center=true);
        }
    }

    module encoder_cutout() {
        encoder_base_height_offset = top_of_pcb + encoder_base_height;
        encoder_y_offset = (display_width / 2) + (7.1 * 2);

        translate([0, encoder_y_offset, encoder_base_height_offset]) {
            rotate(90)
                cube([encoder_width + encoder_cutout_tolerance,
                      encoder_length + encoder_cutout_tolerance,
                      encoder_base_height],
                     center=true);
        }
    }
    
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

    module mount_post(x, y) {
        height = outside_top_of_enclosure - pcb_offset - (pcb_height / 2);
        z = outside_top_of_enclosure - (height / 2);
        difference() {
            translate([x, y, z])
                cylinder(h=height, d=mount_post_diameter, center=true, $fn=32);
            translate([x, y, 4.5]) {
                rotate(a=[0, 0, 0]) {
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

    module lid_screw_post(x, y) {
        z = outside_bottom_of_enclosure + (lid_screw_height / 2) + enclosure_lip_width;

        difference() {
            translate([x, y, z])
                cube([lid_screw_width,
                      lid_screw_length,
                      lid_screw_height], center=true);
            translate([x, y, z - lid_screw_height / 2])
                screw_hole(DIN965, M3, 10, 7);
        }
    }

    module lid_screws() {
        left_x_offset = (enclosure_width / 2) - (lid_screw_width / 2) - (enclosure_lip_width / 2);
        left_y_offset = 0;
        lid_screw_post(left_x_offset, left_y_offset);

        right_x_offset = -((enclosure_width / 2) - (lid_screw_width / 2) - (enclosure_lip_width / 2));
        right_y_offset = 0;
        lid_screw_post(right_x_offset, right_y_offset);
    }

    module outer_shell() {
        difference() {
            enclosure_piece(true);
            headphone_cutout();
            usb_cutout();
            switch_cutout();
            display_cutout();
            encoder_cutout();
        }
        lid_screws();
    }

    union() {
        outer_shell();
        mount_posts();
    }
}

module enclosure_piece(center) {
    difference() {
        rounded_octagon(enclosure_width,
                enclosure_length,
                enclosure_height / 2,
                center=center);
        translate([0, 0, -enclosure_lip_width]) {
            rounded_octagon(enclosure_width - enclosure_lip_width,
                    enclosure_length - enclosure_lip_width,
                    (enclosure_height / 2) + enclosure_lip_width,
                    center=center);
        }
    }
}

module rounded_octagon(width, length, height, center=false) {
    diameter = width / 15;

    module hull_post(hpx, hpy) {
        translate([hpx,
                   hpy,
                   -(height/2)])
            cylinder(d=diameter,
                     h=height);
    }

    module hull_posts() {
        hull_post((width / 2) - (diameter / 4),
                  (length / 4) - (diameter / 2));
        hull_post(-((width / 2) - (diameter / 4)),
                  (length / 4) - (diameter / 2));
        hull_post((width / 4) - (diameter / 4),
                  (length / 2) - (diameter / 2));
        hull_post(-((width / 4) - (diameter / 4)),
                  (length / 2) - (diameter / 2));

        hull_post((width / 2) - (diameter / 4),
                  -((length / 4) - (diameter / 2)));
        hull_post(-((width / 2) - (diameter / 4)),
                  -((length / 4) - (diameter / 2)));
        hull_post((width / 4) - (diameter / 4),
                  -((length / 2) - (diameter / 2)));
        hull_post(-((width / 4) - (diameter / 4)),
                  -((length / 2) - (diameter / 2)));
    }

    hull() {
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
        hull_posts();
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

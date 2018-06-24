$fn = 10;

total_1u_count = 12;
row_count = 5;

switch_cutout_1u_width = 14.0;
switch_cutout_1u_length = 14.0;
switch_cutout_1u_padding = 5.05;
switch_cutout_1u_pitch = switch_cutout_1u_width + switch_cutout_1u_padding;

top_plate_padding_top_bottom = 0;
top_plate_padding_left_right = 0;
top_plate_height = 1.6;
top_plate_width = (row_count * switch_cutout_1u_pitch) + top_plate_padding_top_bottom;
top_plate_length = (total_1u_count * switch_cutout_1u_pitch) + top_plate_padding_left_right;

spacebar_length = switch_cutout_1u_width * 7;
spacebar_width = switch_cutout_1u_width;

plate_height_spacing = 5.0 + 0.3;

union() {
    top_plate();
}

module top_plate() {
    module rounded_corners() {
        corner_radius = 3;
        translate([-(top_plate_length / 2), (top_plate_width / 2)])
            circle(r=corner_radius);
        translate([-(top_plate_length / 2), -(top_plate_width / 2)])
            circle(r=corner_radius);
        translate([(top_plate_length / 2), (top_plate_width / 2)])
            circle(r=corner_radius);
        translate([(top_plate_length / 2), -(top_plate_width / 2)])
            circle(r=corner_radius);
    }
    
    difference() {
        color("gray", 1.0)
            hull() {
            square([top_plate_length,
                    top_plate_width],
                   center = true);
            rounded_corners();
        }
        union() {
            row_1_switch_cutout();
            row_2_switch_cutout();
            row_3_switch_cutout();
            row_4_switch_cutout();
            row_5_switch_cutout();
            mounting_holes();
        }
    }
}

module row_switch_cutout(row, switch_offset, cutout_count, add_small_stabilizer=false) {
    start_x_offset = (top_plate_length / 2) - (switch_cutout_1u_pitch / 2) - (top_plate_padding_left_right / 2) - (switch_cutout_1u_pitch * switch_offset);
    start_y_offset = (top_plate_width / 2) - (switch_cutout_1u_pitch * row) + (switch_cutout_1u_pitch / 2) - (top_plate_padding_top_bottom / 2);

    for (x = [0:cutout_count - 1]) {
        cherry_mx_cutout(start_x_offset - (x * switch_cutout_1u_pitch),
                         start_y_offset,
                         switch_cutout_1u_width,
                         switch_cutout_1u_length,
                         add_small_stabilizer);
    }
}

module row_1_switch_cutout() {
    row_switch_cutout(row=1, switch_offset=0, cutout_count=total_1u_count);
}

module row_2_switch_cutout() {
    row_switch_cutout(row=2, switch_offset=0, cutout_count=total_1u_count);
}

module row_3_switch_cutout() {
    row_switch_cutout(row=3, switch_offset=0, cutout_count=total_1u_count);
}

module row_4_switch_cutout() {
    row_switch_cutout(row=4, switch_offset=0, cutout_count=total_1u_count);
}

module row_5_switch_cutout() {
    row_switch_cutout(row=5, switch_offset=0, cutout_count=5);
    row_switch_cutout(row=5, switch_offset=5.5, cutout_count=1, add_small_stabilizer=true);
    row_switch_cutout(row=5, switch_offset=7, cutout_count=5);
}

module cherry_mx_cutout(x, y, switch_cutout_width, switch_cutout_length, add_small_stabilizer=false) {
    module rounded_corners() {
        corner_radius = 0.3;
        translate([x + (switch_cutout_length / 2), y + (switch_cutout_width / 2)])
            circle(r = corner_radius, center = true);
        translate([x + (switch_cutout_length / 2), y - (switch_cutout_width / 2)])
            circle(r = corner_radius, center = true);
        translate([x - (switch_cutout_length / 2), y + (switch_cutout_width / 2)])
            circle(r = corner_radius, center = true);
        translate([x - (switch_cutout_length / 2), y - (switch_cutout_width / 2)])
            circle(r = corner_radius, center = true);
    }

    hull() {
        translate([x, y])
            square([switch_cutout_length,
                    switch_cutout_width],
                center=true);
        rounded_corners();
    }

    if (add_small_stabilizer) {
        small_stabilizer(x - switch_cutout_length, y, false);
        small_stabilizer(x + switch_cutout_length, y, true);
    }
}

module small_stabilizer(x, y, right=false) {
    stabilizer_length = 6.65 + 0.1;
    stabilizer_width = 13.46 + 0.15;

    bottom_square_length = 3.04 + 0.1;
    bottom_square_width = 1.16 + 0.254;

    left_square_length = 0.762;
    left_square_width = 2.79 + 0.2;
    left_square_width_offset = 0.5;

    right_square_length = switch_cutout_1u_length - (stabilizer_length);
    right_square_width = stabilizer_width - (2 * (0.81 + 0.1));

    translate([x, y]) {
        mirror([right ? 1 : 0, 0, 0]) {
            union() {
                square([stabilizer_length,
                        stabilizer_width],
                       center=true);
                translate([0, -(stabilizer_width / 2) - (bottom_square_width / 2) + 0.01]) {
                    square([bottom_square_length,
                            bottom_square_width],
                           center=true);
                }
                translate([-(stabilizer_length / 2) - (left_square_length / 2) + 0.01, (left_square_width / 2) - left_square_width_offset]) {
                    square([left_square_length,
                            left_square_width],
                           center=true);
                }
                translate([(stabilizer_length / 2) + (right_square_length / 2) - 0.01, 0]) {
                    square([right_square_length,
                            right_square_width],
                           center=true);
                }
            }
        }
    }
}

module mounting_holes() {
    module mounting_hole(x, y) {
        drill_size = 2.10;
        translate([x, y])
            circle(d=drill_size);
    }

    mounting_hole(0, 2 * switch_cutout_1u_pitch);
    mounting_hole(0, -switch_cutout_1u_pitch);

    mounting_hole(-(5 * switch_cutout_1u_pitch), 2 * switch_cutout_1u_pitch);
    mounting_hole(-(5 * switch_cutout_1u_pitch), -(2 * switch_cutout_1u_pitch));

    mounting_hole((5 * switch_cutout_1u_pitch), 2 * switch_cutout_1u_pitch);
    mounting_hole((5 * switch_cutout_1u_pitch), -(2 * switch_cutout_1u_pitch));
}

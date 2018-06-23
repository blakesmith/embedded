$fn = 10;

cherry_switch_length = 15.6;
cherry_switch_width = 15.6;
cherry_switch_housing_height = 6.6;
cherry_switch_housing_height = 5.0;
cherry_switch_switch_height = 3.6;

total_1u_count = 14;
row_count = 5;

switch_cutout_width = 14.0;
switch_cutout_length = 14.0;
switch_cutout_padding = 5.05;
switch_cutout_pitch = switch_cutout_width + switch_cutout_padding;

top_plate_padding_top_bottom = 5.05;
top_plate_padding_left_right = 5.05;
top_plate_height = 1.6;
top_plate_width = (row_count * switch_cutout_pitch) + top_plate_padding_top_bottom;
top_plate_length = (total_1u_count * switch_cutout_pitch) + top_plate_padding_left_right;

spacebar_length = switch_cutout_width * 7;
spacebar_width = switch_cutout_width;

plate_height_spacing = 5.0 + 0.3;

union() {
    top_plate();
}

module top_plate() {
    top_plate_x = 0;
    top_plate_y = 0;
    top_plate_z = 0;

    difference() {
        translate([top_plate_x, top_plate_y, top_plate_z])
            color("gray", 1.0)
            square([top_plate_length,
                    top_plate_width],
                 center = true);
        union() {
            row_1_switch_cutout();
            row_2_switch_cutout();
            row_3_switch_cutout();
            row_4_switch_cutout();
            row_5_switch_cutout();
        }
    }
}

module uniform_row_switch_cutout(start_x_offset, start_y_offset, cutout_count, key_size) {
    for (x = [0:cutout_count - 1]) {
        cherry_mx_cutout(start_x_offset + (x * switch_cutout_pitch),
                         start_y_offset,
                         key_size);
    }
}

module row_1_switch_cutout() {
    start_x_offset = -(top_plate_length / 2) + (switch_cutout_pitch / 2) + (top_plate_padding_left_right / 2);
    start_y_offset = (top_plate_width / 2) - switch_cutout_pitch + (switch_cutout_pitch / 2) - (top_plate_padding_top_bottom / 2);
    cutout_count = 14;
    uniform_row_switch_cutout(start_x_offset, start_y_offset, cutout_count, key_size=1);
}

module row_2_switch_cutout() {
    start_x_offset = -(top_plate_length / 2) + (switch_cutout_pitch / 2) + (top_plate_padding_left_right / 2);
    start_y_offset = (top_plate_width / 2) - (switch_cutout_pitch * 2) + (switch_cutout_pitch / 2) - (top_plate_padding_top_bottom / 2);
    cutout_count = 14;
    uniform_row_switch_cutout(start_x_offset, start_y_offset, cutout_count, key_size=1);
}

module row_3_switch_cutout() {
    start_x_offset = -(top_plate_length / 2) + (switch_cutout_pitch / 2) + (top_plate_padding_left_right / 2);
    start_y_offset = (top_plate_width / 2) - (switch_cutout_pitch * 3) + (switch_cutout_pitch / 2) - (top_plate_padding_top_bottom / 2);
    cutout_count = 14;
    uniform_row_switch_cutout(start_x_offset, start_y_offset, cutout_count, key_size=1);
}

module row_4_switch_cutout() {
    start_x_offset = -(top_plate_length / 2) + (switch_cutout_pitch / 2) + (top_plate_padding_left_right / 2);
    start_y_offset = (top_plate_width / 2) - (switch_cutout_pitch * 4) + (switch_cutout_pitch / 2) - (top_plate_padding_top_bottom / 2);
    cutout_count = 14;
    uniform_row_switch_cutout(start_x_offset, start_y_offset, cutout_count, key_size=1);
}

module row_5_switch_cutout() {
    start_x_offset = -(top_plate_length / 2) + (switch_cutout_pitch / 2) + (top_plate_padding_left_right / 2);
    start_y_offset = (top_plate_width / 2) - (switch_cutout_pitch * 5) + (switch_cutout_pitch / 2) - (top_plate_padding_top_bottom / 2);
    cutout_count = 14;
    uniform_row_switch_cutout(start_x_offset, start_y_offset, cutout_count, key_size=1);
}

module cherry_mx_cutout(x, y, key_size) {
    corner_radius = 0.3;
    hull() {
        translate([x, y, z])
            square([switch_cutout_length * key_size,
                    switch_cutout_width * key_size],
                center=true);
        union() {
            translate([x + (switch_cutout_length / 2), y + (switch_cutout_width / 2)])
                circle(r = corner_radius, center = true);
            translate([x + (switch_cutout_length / 2), y - (switch_cutout_width / 2)])
                circle(r = corner_radius, center = true);
            translate([x - (switch_cutout_length / 2), y + (switch_cutout_width / 2)])
                circle(r = corner_radius, center = true);
            translate([x - (switch_cutout_length / 2), y - (switch_cutout_width / 2)])
                circle(r = corner_radius, center = true);
        }
    }
}

module cherry_mx_switch(x, y, z) {
    
}

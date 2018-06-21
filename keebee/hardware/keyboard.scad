cherry_switch_length = 15.6;
cherry_switch_width = 15.6;
cherry_switch_housing_height = 6.6;
cherry_switch_housing_height = 5.0;
cherry_switch_switch_height = 3.6;

total_cutout_count = 14;
row_count = 5;

switch_cutout_width = 14.0;
switch_cutout_length = 14.0;
switch_cutout_padding = 5.5;
switch_cutout_pitch = switch_cutout_width + switch_cutout_padding;

top_plate_padding_top_bottom = 3.0;
top_plate_padding_left_right = 3.0;
top_plate_height = 1.6;
top_plate_width = (row_count * switch_cutout_pitch) + (top_plate_padding_top_bottom * 2);
top_plate_length = (total_cutout_count * switch_cutout_pitch) + (top_plate_padding_left_right * 2);

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
            cube([top_plate_length,
                  top_plate_width,
                  top_plate_height],
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

module uniform_row_switch_cutout(start_x_offset, start_y_offset, cutout_count) {
    start_z_offset = -2.0;

    for (x = [0:cutout_count - 1]) {
        translate([start_x_offset + (x * switch_cutout_pitch),
                   start_y_offset,
                   start_z_offset])
            cube([switch_cutout_length,
                  switch_cutout_width,
                  10.0]);
    }
}

module row_1_switch_cutout() {
    start_x_offset = -(top_plate_length / 2) + top_plate_padding_left_right + (switch_cutout_padding / 2);
    start_y_offset = (top_plate_width / 2) - switch_cutout_pitch + top_plate_padding_top_bottom - (switch_cutout_padding / 2);
    cutout_count = 14;
    uniform_row_switch_cutout(start_x_offset, start_y_offset, cutout_count);
}

module row_2_switch_cutout() {
    start_x_offset = -(top_plate_length / 2) + top_plate_padding_left_right + (switch_cutout_padding / 2);
    start_y_offset = (top_plate_width / 2) - (switch_cutout_pitch * 2) + top_plate_padding_top_bottom - (switch_cutout_padding / 2);
    cutout_count = 14;
    uniform_row_switch_cutout(start_x_offset, start_y_offset, cutout_count);
}

module row_3_switch_cutout() {
    start_x_offset = -(top_plate_length / 2) + top_plate_padding_left_right + (switch_cutout_padding / 2);
    start_y_offset = (top_plate_width / 2) - (switch_cutout_pitch * 3) + top_plate_padding_top_bottom - (switch_cutout_padding / 2);
    cutout_count = 14;
    uniform_row_switch_cutout(start_x_offset, start_y_offset, cutout_count);
}

module row_4_switch_cutout() {
    start_x_offset = -(top_plate_length / 2) + top_plate_padding_left_right + (switch_cutout_padding / 2);
    start_y_offset = (top_plate_width / 2) - (switch_cutout_pitch * 4) + top_plate_padding_top_bottom - (switch_cutout_padding / 2);
    cutout_count = 14;
    uniform_row_switch_cutout(start_x_offset, start_y_offset, cutout_count);
}

module row_5_switch_cutout() {
    start_x_offset = -(top_plate_length / 2) + top_plate_padding_left_right + (switch_cutout_padding / 2);
    start_y_offset = (top_plate_width / 2) - (switch_cutout_pitch * 5) + top_plate_padding_top_bottom - (switch_cutout_padding / 2);
    cutout_count = 14;
    uniform_row_switch_cutout(start_x_offset, start_y_offset, cutout_count);
}

module cherry_mx_cutout(x, y, z) {
}

module cherry_mx_switch(x, y, z) {
    
}

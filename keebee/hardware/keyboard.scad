top_plate_height = 1.6;
top_plate_width = 101.60;
top_plate_length = 294.64;

cherry_switch_length = 15.6;
cherry_switch_width = 15.6;
cherry_switch_housing_height = 6.6;
cherry_switch_housing_height = 5.0;
cherry_switch_switch_height = 3.6;

switch_cutout_width = 14.0;
switch_cutout_length = 14.0;
switch_cutout_pitch = switch_cutout_width + 5.5;

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

module uniform_row_switch_cutout(start_y_offset) {
    cutout_count = 14;

    start_x_offset = -(top_plate_length / 2) + 3.0;
    start_z_offset = -2.0;

    for (x = [0:cutout_count]) {
        translate([start_x_offset + (x * switch_cutout_pitch),
                   start_y_offset,
                   start_z_offset])
            cube([switch_cutout_length,
                  switch_cutout_width,
                  10.0]);
    }
}

module row_1_switch_cutout() {
    start_y_offset = (top_plate_width / 2) - switch_cutout_width - 3.0;
    uniform_row_switch_cutout(start_y_offset);
}

module row_2_switch_cutout() {
    start_y_offset = (top_plate_width / 2) - (switch_cutout_pitch * 2);
    uniform_row_switch_cutout(start_y_offset);
}

module row_3_switch_cutout() {
    start_y_offset = (top_plate_width / 2) - (switch_cutout_pitch * 3);
    uniform_row_switch_cutout(start_y_offset);
}

module row_4_switch_cutout() {
    start_y_offset = (top_plate_width / 2) - (switch_cutout_pitch * 4);
    uniform_row_switch_cutout(start_y_offset);
}

module row_5_switch_cutout() {
    start_y_offset = (top_plate_width / 2) - (switch_cutout_pitch * 5);
    uniform_row_switch_cutout(start_y_offset);
}

module cherry_mx_cutout(x, y, z) {
}

module cherry_mx_switch(x, y, z) {
    
}

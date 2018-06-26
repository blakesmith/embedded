$fn = 10;

total_1u_count = 14;
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

echo("Top plate base width", top_plate_width, "Top plate length", top_plate_length);

spacebar_length = switch_cutout_1u_width * 7;
spacebar_width = switch_cutout_1u_width;

plate_height_spacing = 5.0 + 0.3;

cherry_top_height = 3.6;
cherry_middle_height = 6.6;
cherry_bottom_width = 15.6;
cherry_bottom_length = 15.6;

dsa_keycap_bottom_width = 18.415;
dsa_keycap_bottom_length = 18.415;
dsa_keycap_top_length = 12.7;
dsa_keycap_top_width = 12.7;
dsa_keycap_height = 7.39;

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
            row_0_switch_cutout();
            row_1_switch_cutout();
            row_2_switch_cutout();
            row_3_switch_cutout();
            row_4_switch_cutout();
            mounting_holes();
        }
    }
}

DVORAK_KEY_LABELS = [
    ["ESC",   "1",   "2",   "3", "4", "5", "6",    "7",   "8",   "9",  "0", "[",     "]",   "BS"],
    ["TAB",   "'",   ",",   ".", "P", "Y", "F",    "G",   "C",   "R",  "L", "/",     "=",   "\\"],
    ["CTRL",  "A",   "O",   "E", "U", "I", "D",    "H",   "T",   "N",  "S", "-",     "ENT", ""  ],
    ["SHIFT", ";",   "Q",   "J", "K", "X", "B",    "M",   "W",   "V",  "Z", "SHIFT", "↑",   " " ],
    ["CTRL",  "SUP", "ALT", " ", " ", " ", "SPC",  " ",   "ALT", "FN", " ", "←",     "↓",   "→" ]
];

DVORAK_SHIFT_KEY_LABELS = [
    ["`", "!",  "@", "#", "$", "%", "^", "&", "*", "(", ")", "{", "}", " "],
    [" ", "\"", "<", ">", " ", " ", " ", " ", " ", " ", " ", "?", "+", "|"],
    [" ", " ",  " ", " ", " ", " ", " ", " ", " ", " ", " ", "_", " ", " "],
    [" ", ":",  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "],
    []
];

DVORAK_FN_KEY_LABELS = [
    ["~", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "DEL"],
    [],
    [],
    [],
    []
];

TROPIC_PALLETTE = [
    [246, 66, 66],
    [255, 138, 34],
    [163, 232, 220]
];

BLUE_PALLETTE = [
    [0, 81, 255],
    [47, 134, 255],
    [81, 172, 255],
];

BLUE_DREAM_PALLETTE = [
    [15, 29, 9],
    [18, 200, 253],
    [236, 235, 245]
];

MUTE_PALLETTE = [
    [39, 86, 123],
    [182, 59, 59],
    [249, 196, 20]
];

KEYCAP_PALLETTE = BLUE_DREAM_PALLETTE;

C1 = [KEYCAP_PALLETTE[0][0] / 255, KEYCAP_PALLETTE[0][1] / 255, KEYCAP_PALLETTE[0][2] / 255];
C2 = [KEYCAP_PALLETTE[1][0] / 255, KEYCAP_PALLETTE[1][1] / 255, KEYCAP_PALLETTE[1][2] / 255];
C3 = [KEYCAP_PALLETTE[2][0] / 255, KEYCAP_PALLETTE[2][1] / 255, KEYCAP_PALLETTE[2][2] / 255];

KEYCAP_COLORS = [
    [C1, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2],
    [C2, C3, C3, C3, C3, C3, C3, C3, C3, C3, C3, C3, C3, C2],
    [C2, C3, C3, C3, C3, C3, C3, C3, C3, C3, C3, C3, C2, C2],
    [C2, C3, C3, C3, C3, C3, C3, C3, C3, C3, C3, C2, C1, C2],
    [C2, C2, C2, C2, C2, C2, C1, C2, C2, C2, C2, C1, C1, C1]
];

module key_label(row, i, x, y, label_color="red", shift_color="green", fn_color="orange") {
    offset_z = cherry_middle_height + cherry_top_height;
    translate([x, y, offset_z]) {
        color(label_color, 1.0)
            text(DVORAK_KEY_LABELS[row][i], halign="center", valign="center", size=4);
        translate([-(switch_cutout_1u_pitch / 4), (switch_cutout_1u_pitch / -4)])
            color(shift_color, 1.0)
            text(DVORAK_SHIFT_KEY_LABELS[row][i], halign="center", valign="center", size=3);
        translate([switch_cutout_1u_pitch / 4, switch_cutout_1u_pitch / -4])
            color(fn_color, 1.0)
            text(DVORAK_FN_KEY_LABELS[row][i], halign="center", valign="center", size=3);
    }
}

module row_switch_cutout(row, switch_offset, cutout_count, switch_size=1, add_small_stabilizer=false) {
    start_x_offset = -(top_plate_length / 2) + (switch_cutout_1u_pitch / 2) + (top_plate_padding_left_right / 2) + (switch_cutout_1u_pitch * switch_offset);
    start_y_offset = (top_plate_width / 2) - (switch_cutout_1u_pitch * (row + 1)) + (switch_cutout_1u_pitch / 2) - (top_plate_padding_top_bottom / 2);

    for (i = [0:cutout_count - 1]) {
        x_offset = start_x_offset + (i * switch_cutout_1u_pitch);
        y_offset = start_y_offset;

        cherry_mx_cutout(x_offset,
                         y_offset,
                         switch_cutout_1u_width,
                         switch_cutout_1u_length,
                         add_small_stabilizer);
        %dsa_keycap(x_offset, y_offset, KEYCAP_COLORS[row][i + floor(switch_offset)], switch_size);
        %cherry_mx_switch(x_offset, y_offset);
        %key_label(row, i + floor(switch_offset), x_offset, y_offset);
    }
}

module row_0_switch_cutout() {
    row_switch_cutout(row=0, switch_offset=0, cutout_count=total_1u_count);
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
    row_switch_cutout(row=4, switch_offset=0, cutout_count=6);
    row_switch_cutout(row=4, switch_offset=6.5, cutout_count=1, switch_size=2, add_small_stabilizer=true);
    row_switch_cutout(row=4, switch_offset=8, cutout_count=6);
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

module cherry_mx_switch(x, y) {
    offset_z = cherry_middle_height / 2;
    translate([x, y, offset_z]) {
        color("black", 1.0)
        linear_extrude(height = cherry_middle_height,
                       center = true,
                       scale = 0.69)
            square([cherry_bottom_width,
                    cherry_bottom_length],
                   center=true);
    }
}

module dsa_keycap(x, y, cap_color, switch_size) {
    offset_z = (dsa_keycap_height / 2) + cherry_middle_height - cherry_top_height;
    translate([x, y, offset_z]) {
        color(cap_color, 1.0)
            linear_extrude(height = dsa_keycap_height, center = true, scale = 0.69)
            square([dsa_keycap_bottom_width * switch_size,
                    dsa_keycap_bottom_length],
                   center=true);
    }
}

module mounting_holes() {
    module mounting_hole(x, y) {
        drill_size = 2.10;
        translate([x, y])
            circle(d=drill_size);
    }

    y_offset = ((row_count - 1 )/ 2) * switch_cutout_1u_pitch;
    x_offset = ((total_1u_count / 2) - 1) * switch_cutout_1u_pitch;

    mounting_hole(0, y_offset);
    mounting_hole(0, -switch_cutout_1u_pitch);

    mounting_hole(-x_offset, y_offset);
    mounting_hole(-x_offset, -y_offset);

    mounting_hole(x_offset, y_offset);
    mounting_hole(x_offset, -y_offset);
}

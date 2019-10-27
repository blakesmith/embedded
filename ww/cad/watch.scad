$fn = 100;

strap_width = 22;
strap_length = 40;
ws2812_length = 5;
ws2812_width = 5;

light_rows = 4;
light_columns = 3;

face_width = strap_width * 1.5;
face_length = 40;
face_height = 5;

lug_width = (face_width - strap_width) / 2;
lug_length = 7;
lug_height = face_height;

pcb_thickness = 1.6;

union() {
    %straps();
    face();
    lugs();
}

module face() {
    cube([face_width, face_length, face_height], center=true);
    %lights();
}

module lug() {
    intersection() {
        cube([lug_width, lug_length, lug_height], center=true);
        translate([10 / 5, -10 / 4, 0])
            cylinder(h=lug_height, d=10, center=true);
    }
}

module lugs() {
    translate([-face_width / 2 + lug_width / 2,
               face_length / 2 + lug_length / 2,
               0])
        mirror([0, 0, 0])
        lug();
    translate([face_width / 2 - lug_width / 2,
               face_length / 2 + lug_length / 2,
               0])
        mirror([1, 0, 0])
        lug();
    translate([face_width / 2 - lug_width / 2,
               -face_length / 2 - lug_length / 2,
               0])
        mirror([0, 1, 0])
        mirror([1, 0, 0])
        lug();
    translate([-face_width / 2 + lug_width / 2,
               -face_length / 2 - lug_length / 2,
               0])
        mirror([0, 1, 0])
        lug();
}

module lights() {
    light_margin_x = ws2812_width / 2;
    light_margin_y = ws2812_length / 2;
    
    light_padding_x = face_width - (ws2812_width * light_columns) - light_margin_x;
    light_padding_y = face_length - (ws2812_length * light_rows) - light_margin_y;

    light_pitch_x = ws2812_width + (light_padding_x / (light_columns - 1));
    light_pitch_y = ws2812_length + (light_padding_y / (light_rows - 1));

    start_offset_x = -1 * (face_width  / 2) + (ws2812_width / 2) + (light_margin_x / 2);
    start_offset_y = -1 * (face_length / 2) + (ws2812_length / 2) + (light_margin_y / 2);
    
    for (i = [0:light_columns - 1]) {
        for (y = [0:light_rows - 1]) {
            translate([start_offset_x + (i * light_pitch_x),
                       start_offset_y + (y * light_pitch_y),
                       face_height / 2])
                color("red")
                cube([ws2812_width, ws2812_length, 1], center=true);
        }
    }
}

module straps() {
    color("gray") {
        translate([0, -strap_length, 0])
            cube([strap_width, strap_length, 1], center=true);
        translate([0, strap_length, 0])
            cube([strap_width, strap_length, 1], center=true);
    }
}

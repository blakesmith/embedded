pcb_height = 58.420;
pcb_length = 45.720;
pcb_thickness = 1.6; // TODO: double check, add tolerance

stand_width = pcb_length + 4;
stand_length = 30.0;
stand_height = 10.0;

cutout_length = pcb_length;
cutout_thickness = pcb_thickness;
cutout_depth = 5.0;

union() {
    stand();
}

module stand() {
    cutout_x = -(pcb_length / 2);
    cutout_y = -(cutout_thickness / 2);
    cutout_z = (stand_height / 2) - cutout_depth + 1;

    difference() {
        cube([stand_width,
              stand_length,
              stand_height],
             center = true);
        translate([cutout_x, cutout_y, cutout_z])
            cube([cutout_length,
                  cutout_thickness,
                  cutout_depth],
                 cunter = true);
    }
}

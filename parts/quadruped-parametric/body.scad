use <electronics_enclosure_01.scad>;
use <hip.scad>;
use <backbone.scad>;

servo_length = 23.5;
servo_width = 12.5;

bb_length=100;
bb_width=14;
bb_height=8;

common_base_width = 60;
common_base_depth = 4.5;
common_base_height = 4;

enclosureWithHips();
//newBackbone();

module joiner() {
  translate([-common_base_width/2, -common_base_depth/2 + 30, 0])
    cube([common_base_width, common_base_depth, common_base_height]);
}

module enclosureWithHips() {
  union() {
    rotate([0, 0, 90])
      translate([-58/2, -73/2, 0])
        enclosure();

    translate([0,  40, 0])
      hip(servo_length, servo_width);

    translate([0, -40, 0])
      hip(servo_length, servo_width);

    joiner();
    mirror([0, 1, 0]) joiner();
  };
};

module newBackbone() {
  difference() {
    union() {
      translate([0, 0, -bb_height/2+1])
        backbone(bb_length,bb_width,bb_height,servo_length,servo_width);

      tab();
      mirror([0,1,0]) tab();
    };

    enclosureWithHips();
  }
};

module tab() {
  translate([0, 0, 0]) {
    difference() {
      translate([-7, 49, -bb_height+1])
        cube([14, 3, bb_height+4.5]);

      translate([-10, 47.7, 0.7])
        rotate([55, 0, 0])
          cube([20, 4, 5]);

      translate([-10, 46.75, 8])
        rotate([-55, 0, 0])
          cube([20, 4, 5]);
      
    }
  }
}
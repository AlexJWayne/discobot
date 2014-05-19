// PWM Controller Board dimensions
pwmWidth = 26;
pwmLength = 63;
pwmScrewHoleInset = 3.2;
pwmScrewHoleDiameter = 3.5;
pwmClearance = 24;

// NeoPixel Shield dimensions
neoWidth = 54.5;
neoLength = 69.5;

// cutouts
cutoutWidth = 5;
cutoutHeight = 20;

// center
centerHoleDiameter = 4;

// Padding between cavity and outer edge
wallWidth = 1.5;


// Go!
difference() {
  union() {
    walledEnclosure();
    shelves();
  }
  pwmScrewHoles();
  cutouts();
  centerHole();
};


module walledEnclosure() {
  difference(){
    // Main container
    cube([
      neoWidth + wallWidth*2,
      neoLength + wallWidth*2,
      pwmClearance + wallWidth*2
    ]);

    // Hollow center
    translate([wallWidth, wallWidth, wallWidth]) {
      cube([
        neoWidth,
        neoLength,
        pwmClearance*2
      ]);
    };
  };
};

module screwHole(x, y) {
  translate([x, y, -10]) {
    cylinder(
      h   = pwmClearance,
      d   = pwmScrewHoleDiameter,
      $fn = 40
    );
  };
};

module pwmScrewHoles() {
  screwHole(
    wallWidth + (neoWidth / 2)  - (pwmWidth / 2)  + pwmScrewHoleInset,
    wallWidth + (neoLength / 2) - (pwmLength / 2) + pwmScrewHoleInset
  );
  screwHole(
    wallWidth + (neoWidth / 2)  + (pwmWidth / 2)  - pwmScrewHoleInset,
    wallWidth + (neoLength / 2) - (pwmLength / 2) + pwmScrewHoleInset
  );
  screwHole(
    wallWidth + (neoWidth / 2)  - (pwmWidth / 2)  + pwmScrewHoleInset,
    wallWidth + (neoLength / 2) + (pwmLength / 2) - pwmScrewHoleInset
  );
  screwHole(
    wallWidth + (neoWidth / 2)  + (pwmWidth / 2)  - pwmScrewHoleInset,
    wallWidth + (neoLength / 2) + (pwmLength / 2) - pwmScrewHoleInset
  );
};

module shelf() {
  rotate([82, 0, 0]) {
    translate([wallWidth*2, pwmClearance*.65+wallWidth, .4]) {
      cube([neoWidth - wallWidth*2, pwmClearance/3, 2]);
    };
  };
};

module shelves() {
  shelf();
  translate([0, neoLength + wallWidth*2, 0])
    mirror([0,1,0])
      shelf();
};

module cutouts() {
  translate([
    -25,
    neoLength/2 - cutoutWidth/2 + wallWidth,
    pwmClearance/4 + wallWidth,
  ]) {
    cube([100, cutoutWidth, cutoutHeight]);
  }
}

module centerHole() {
  translate([
    wallWidth + neoWidth/2,
    wallWidth + neoLength/2,
    0,
  ]) {
    cylinder(
      h = 100,
      d = centerHoleDiameter,
      $fn = 40
    );

    translate([0,0, wallWidth-1])
      cylinder(
        h = 2,
        d = centerHoleDiameter*2,
        $fn = 40
      );
  };
}

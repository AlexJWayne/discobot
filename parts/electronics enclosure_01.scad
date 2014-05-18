// PWM Controller Board dimensions
pwmWidth = 26;
pwmLength = 63;
pwmScrewHoleInset = 3;
pwmScrewHoleDiameter = 3;
pwmClearance = 24;

// NeoPixel Shield dimensions
neoWidth = 54;
neoLength = 69;

// cutouts
cutoutWidth = 5;
cutoutHeight = 12;

// center
centerHoleDiameter = 5;

// Padding between cavity and outer edge
wallWidth = 2;


// Go!
difference() {
  union() {
    shelves();
    walledEnclosure();
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
    translate([wallWidth*2, pwmClearance*.65+wallWidth, .45]) {
      cube([neoWidth - wallWidth*2, pwmClearance/3, 2]);
    };
  };
};

module shelves() {
  shelf();
  translate([0, neoLength + 6 - wallWidth, 0])
    mirror([0,1,0])
      shelf();
};

module cutouts() {
  for (i = [1:3]) {
    translate([
      -25,
      i*neoWidth/3,
      pwmClearance - cutoutHeight - wallWidth,
    ]) {
      cube([100, cutoutWidth, cutoutHeight]);
    }
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
      d = centerHoleDiameter*1.5,
      $fn = 40
    );
  };
}

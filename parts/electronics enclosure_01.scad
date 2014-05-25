// PWM Controller Board dimensions
pwmWidth = 26;
pwmLength = 63;
pwmScrewHoleInset = 3.2;
pwmScrewHoleDiameter = 3.5;
pwmClearance = 25;


// NeoPixel Shield dimensions
neoWidth = 54.5;
neoLength = 70;
neoClearance = 15;

// cutouts
cutoutWidth = 4;
cutoutHeight = neoLength - 25;

// center
centerHoleDiameter = 5;

// Padding between cavity and outer edge
wallWidth = 1.5;


// Go!
difference() {
  union() {
    walledEnclosure();
    shelves();
    shelf2();
  }
  pwmScrewHoles();
  cutouts();
  centerHole();
  topSlice();
};

module walledEnclosure() {
  difference(){
    // Main container
    cube([
      neoWidth + wallWidth*2,
      neoLength + wallWidth*2,
      pwmClearance + neoClearance + wallWidth*2
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
  translate([
    wallWidth,
    wallWidth,
    .4
  ]) {
    cube([neoWidth, wallWidth, pwmClearance]);
  };
};

module shelves() {
  shelf();
  translate([0, neoLength + wallWidth*2, 0])
    mirror([0,1,0])
      shelf();
};

module cutouts() {
  for (c = [.1, .9]) {
    translate([
      wallWidth + neoWidth*c - cutoutWidth/2,
      wallWidth + neoLength/2 - cutoutHeight/2,
      -10,
    ]) {
      cube([cutoutWidth, cutoutHeight, 100]);
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
        d = centerHoleDiameter*2,
        $fn = 40
      );
  };
}

module shelf2() {
  for (z = [1.5, -1]) {
    for (y = [wallWidth/3-.4, neoWidth+wallWidth/3]) {
      translate([y, wallWidth, pwmClearance + neoClearance + z]) {
        rotate([0, 45, 0]) {
          cube([1.75, neoLength, 1.75]);
        };
      };
    };
  };
};

module topSlice() {
  translate([-20, -20, pwmClearance + neoClearance + 1.6])
    cube([100, 100, 10]);
};

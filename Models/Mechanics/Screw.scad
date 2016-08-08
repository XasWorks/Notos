include <../Values/Values.scad>

module idler_screw(zeroAligned=true) {
  translate([0, 0, (zeroAligned) ? -idlerScrewHeadHeight : 0]) {
    cylinder(d = idlerScrewHeadDiameter, h = idlerScrewHeadHeight);
    translate([0, 0, idlerScrewHeadHeight - 0.0001 ]) cylinder(d = idlerScrewDiameter, h = idlerScrewLength);
  }
}

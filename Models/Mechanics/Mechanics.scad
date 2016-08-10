include <../Values/Values.scad>

module idler_screw(backplate_aligned = true) {
  translate([0, 0, (backplate_aligned) ? - backplateThickness : 0]) {
    cylinder(d = idlerScrewHeadDiameter, h = idlerScrewHeadHeight);
    translate([0, 0, idlerScrewHeadHeight - 0.0001 ]) cylinder(d = idlerScrewDiameter, h = idlerScrewLength);
  }
}

module idler_screw_nut() {
	difference() {
		cylinder(d = idlerNutDiameter, h = idlerNutHeight);
		translate([0, 0, -0.1]) cylinder(d = idlerScrewDiameter, h = idlerNutHeight + 0.2);
	}
}

module ball_bearing() {
	difference() {
		cylinder(d = ballBearingOuterDiameter, h = ballBearingHeight);
		translate([0, 0, -0.1]) cylinder(d = ballBearingInnerDiameter, h = ballBearingHeight + 0.2);
	}
}

ball_bearing();

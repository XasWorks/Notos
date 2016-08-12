include <../Values/Values.scad>

module idler_screw(backplate_aligned = true) {
  translate([0, 0, (backplate_aligned) ? - backplateThickness : 0]) {
	  
    cylinder(d = idlerScrewHeadDiameter + playLooseFit * 2, h = idlerScrewHeadHeight + playTightFit);
    translate([0, 0, idlerScrewHeadHeight - 0.0001 ]) cylinder(d = idlerScrewDiameter + playTightFit * 2, h = idlerScrewLength);
  }
}

module idler_screw_nut() {
	difference() {
		cylinder(d = idlerNutDiameter + playTightFit * 2, h = idlerNutHeight);
		translate([0, 0, -0.1]) cylinder(d = idlerScrewDiameter - playTightFit * 2, h = idlerNutHeight + 0.2);
	}
}

module ball_bearing() {
	difference() {
		cylinder(d = ballBearingOuterDiameter + playTightFit * 2, h = ballBearingHeight);
		translate([0, 0, -0.1]) cylinder(d = ballBearingInnerDiameter - playTightFit * 2, h = ballBearingHeight + 0.2);
	}
}

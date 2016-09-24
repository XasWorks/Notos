include <../Values/Values.scad>

module idler_screw(backplate_aligned = true) {

	totalHeadHeight = idlerScrewHeadHeight + playTightFit;
	totalHeadDiameter = idlerScrewHeadDiameter + playLooseFit * 2;

	totalShaftDiameter = idlerScrewDiameter + playTightFit * 2;

	translate([0, 0, (backplate_aligned) ? - totalHeadHeight : 0]) {

		translate([0, 0, totalHeadHeight - 0.0001 ]) cylinder(d = totalShaftDiameter, h = idlerScrewLength);
		translate([0, 0, totalHeadHeight - idlerScrewHeadSlope - 0.0001]) cylinder(r1 = totalHeadDiameter/2, r2 = totalShaftDiameter/2, h = idlerScrewHeadSlope + 0.0001);
		cylinder(d = totalHeadDiameter, h = totalHeadHeight - idlerScrewHeadSlope);
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

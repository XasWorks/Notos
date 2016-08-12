include <../Values/Values.scad>


use <BasicPlating.scad>
use <../Mechanics/Mechanics.scad>
use <../Mechanics/Motor.scad>
use <TagSystem/Tagging.scad>

module backplate_idlermount() {
	tag("positive", true) cylinder(d = idlerScrewHeadDiameter + IdlerNutMountThickness*2, h = idlerNutHeight);
	tag("negative", false)	idler_screw(true);
}

module backplate_idlermounts() {
	place_at_idlerwheels() backplate_idlermount();
}

module backplate_extra_spots() {
	for(i=[0:len(backplateExtraSpots) - 1]) translate(backplateExtraSpots[i]) circle(r = 0.1);
}

module backplate_outline() {
	hull() {
		plating_outline();
		backplate_extra_spots();
	}
}

module backplate_cut_outline(offset_r = 5) {
	offset(r = offset_r) difference() {
		offset(r = -offset_r) backplate_outline();
		translate([-200, plateGroundClearance + offset_r - 50]) square([400, 50]);
	}
}

module backplate_motor_cut() {
	translate(wheelPositions[0]) motor_cutouts();
}

module backplate_cuts() {
	backplate_motor_cut();
	translate([0, 0, -0.001]) showOnly("negative") backplate_idlermounts();
}

module backplate_basic() {
	translate([0, 0, -backplateThickness]) linear_extrude(height= backplateThickness) backplate_cut_outline();
	backplate_idlermounts();
}

module backplate() {
	difference() {
		backplate_basic();
		backplate_cuts();
	}
}

backplate();

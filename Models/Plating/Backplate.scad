include <../Values/Values.scad>


use <BasicPlating.scad>
use <../Mechanics/Mechanics.scad>
use <../Mechanics/Motor.scad>
use <TagSystem/Tagging.scad>
use <../Modules/ModuleMount.scad>

module backplate_idlermount() {
	tag("positive", true) cylinder(d = idlerScrewHeadDiameter + IdlerNutMountThickness*2, h = idlerNutHeight);
	tag("negative", false)	idler_screw(true);
}

module backplate_extra_spots() {
	for(i=[0:len(backplateExtraSpots) - 1]) translate(backplateExtraSpots[i]) circle(r = 0.1);
}

module backplate_outline() {
	hull() {
		module_screw_outlines();
		plating_outline();
		backplate_extra_spots();
	}
}

module backplate_cut_outline(offset_r = 5) {
	plating_cut_lower() backplate_outline();
}

module backplate_motor_cut() {
	translate(wheelPositions[0]) motor_cutouts();
}

module backplate_cuts() {
	modules_screw_cutouts();
	backplate_motor_cut();
	translate([0, 0, -0.001]) place_at_idlerwheels() showOnly("negative") backplate_idlermount();
}

module backplate_positives() {
	translate([0, 0, -backplateThickness]) linear_extrude(height= backplateThickness) backplate_cut_outline();
	place_at_idlerwheels() backplate_idlermount();
}

module backplate() {
	difference() {
		backplate_positives();
		backplate_cuts();
	}
}

backplate();

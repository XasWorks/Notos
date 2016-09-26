include <../Values/Values.scad>

use <../Tools.scad>

use <BasicPlating.scad>
use <../Mechanics/Mechanics.scad>
use <../Mechanics/Motor.scad>
use <TagSystem/Tagging.scad>
use <../Modules/ModuleMount.scad>
use <PlateConnectors.scad>

module backplate_idlermount() {
	tag("positive", true) {
		cylinder(d = idlerScrewHeadDiameter + idlerNutMountThickness*2, h = plateTrackPlay - plateBearingRingHeight);
		translate([0, 0, plateTrackPlay - plateBearingRingHeight - 0.001]) cylinder(d = idlerScrewDiameter + playTightFit * 2 + plateBearingRingThickness*2, h = plateBearingRingHeight);
	}
	tag("negative", false)	idler_screw(true);
}

module backplate_extra_spots() {
	place_at_array(backplateExtraSpots) circle(r = 0.1);
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
	showOnly("negative") backplate_plate_connectors();
}

module backplate_positives() {
	translate([0, 0, -backplateThickness]) linear_extrude(height= backplateThickness) backplate_cut_outline();
	place_at_idlerwheels() backplate_idlermount();
	backplate_plate_connectors();
}

module backplate() {
	difference() {
		backplate_positives();
		backplate_cuts();
	}
}

backplate();

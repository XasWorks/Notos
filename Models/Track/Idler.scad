include <../Values/Values.scad>
use <Track.scad>

idlerwheel_piece_height = trackWidth/2;

module idlerwheel_bearing_cutouts() tag("negative") {
	cylinder(d = ballBearingOuterDiameter + playTightFit*2, h = ballBearingHeight + 0.1);
}

module idlerwheel_track_teeth_cutouts() tag("negative") {
	track(idlerwheelSize + 0.1, -0.11, clearance_offset = true);
}

iScrewNormalDiameter = idlerScrewDiameter + playLooseFit * 2;
iScrewSpacedDiameter = iScrewNormalDiameter + idlerwheelScrewExtraSpacing*2;
iScrewStartHeight = idlerwheelScrewBushingHeight + 1;
module idlerwheel_screw_start() {

	cylinder(d = iScrewNormalDiameter, h = idlerwheelScrewBushingHeight + 0.01);
	translate([0, 0, idlerwheelScrewBushingHeight]) cylinder(r1 = iScrewNormalDiameter/2, r2 = iScrewSpacedDiameter/2, h = 1.01);
}


module idlerwheel_screw() tag("negative") {

	translate([0, 0, -0.001]) {
		idlerwheel_screw_start();
		translate([0, 0, iScrewStartHeight]) cylinder(d = iScrewSpacedDiameter, h = trackWidth - iScrewStartHeight * 2 + 0.01);
		translate([0, 0, trackWidth + 0.01]) mirror([0, 0, 1]) idlerwheel_screw_start();
	}
}

// Simple repräsentation eines Idler-Rads
module idlerwheel()
	taggedDifference("positive","negative", "neutral") {
	tag("positive") cylinder(r = idlerwheelSize, h = idlerwheel_piece_height - 0.002);

	translate([0, 0, -0.001]) {
		idlerwheel_screw();
		idlerwheel_track_teeth_cutouts();

		idlerwheel_bearing_cutouts();
	}
}

module bearingless_idlerwheel()
taggedDifference("positive", "negative", "neutral") {
	tag("positive") cylinder(r = idlerwheelSize - trackTeethHeight, h = trackWidth);

	tag("positive") translate([0, 0, trackWidth/2]) track_teeth_noslip(idlerwheelSize);
	idlerwheel_screw();
}

bearingless_idlerwheel();

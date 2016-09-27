include <../Values/Values.scad>
use <Track.scad>

idlerwheel_piece_height = trackWidth/2;

module idlerwheel_bearing_cutouts() tag("negative") {
	cylinder(d = ballBearingOuterDiameter + playTightFit*2, h = ballBearingHeight + 0.1);
}

module idlerwheel_track_teeth_cutouts() tag("negative") {
	track(smallWheelSize, clearance_offset = true);
}

module idlerwheel_screw() tag("negative") {
	translate([0, 0, -0.1]) cylinder(d = idlerScrewDiameter + playLooseFit * 2, h = idlerwheel_piece_height + 0.2);
}

// Simple repräsentation eines Idler-Rads
module idlerwheel() taggedDifference(["positive"],["negative"]) {
	tag("positive") cylinder(r = smallWheelSize, h = idlerwheel_piece_height - 0.002);

	translate([0, 0, -0.001]) {
		idlerwheel_screw();
		idlerwheel_track_teeth_cutouts();

		idlerwheel_bearing_cutouts();
	}
}

idlerwheel();

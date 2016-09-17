include <../Values/Values.scad>
use <Track.scad>

idlerwheel_piece_height = trackWidth;

module idlerwheel_bearing_cutouts() render() {
	cylinder(d = ballBearingOuterDiameter + playTightFit*2, h = ballBearingHeight + 0.1);
}

module idlerwheel_track_teeth_cutouts() render() {
	track(smallWheelSize, clearance_offset = true);
}

module idlerwheel_screw() {
	translate([0, 0, -0.1]) cylinder(d = idlerScrewDiameter + playLooseFit * 2, h = idlerwheel_piece_height + 0.2);
}

// Cutouts für das Idler-Wheel, in welche die Schraube, das Kugellager, sowie die Mutter platziert wird.
module idlerwheel_cutouts() render() {
	idlerwheel_screw();
	idlerwheel_track_teeth_cutouts();

	translate([0, 0, idlerwheel_piece_height - (ballBearingHeight)]) idlerwheel_bearing_cutouts();
	idlerwheel_bearing_cutouts();
}

// Simple repräsentation eines Idler-Rads
module idlerwheel() render() {
	difference() {
		cylinder(r = smallWheelSize, h = idlerwheel_piece_height - 0.002);

		translate([0, 0, -0.001]) idlerwheel_cutouts();
	}
}

idlerwheel();

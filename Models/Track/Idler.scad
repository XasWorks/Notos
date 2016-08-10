include <../Values/Values.scad>

idlerwheel_piece_height = trackWidth / 2;

module idlerwheel_bearing_cutouts() render() {
	cylinder(d = ballBearingOuterDiameter + playTightFit*2, h = 100);

	mounthole_diameter = idlerNutDiameter + (frontplateIdlernutMountWallThickness + playTightFit * 2) + playLooseFit * 3;

	translate([0, 0, ballBearingHeight - 0.001]) cylinder(d = mounthole_diameter, h = 100);
}

module idlerwheel_track_teeth_cutouts() render() {
	translate([0, 0, trackTeethNoslip / 2]) difference() {
		cylinder(r = smallWheelSize + 0.1, h = 100);
		cylinder(r = smallWheelSize - trackTeethHeight, h = 100);
	}
}

module idlerwheel_screw() {
	translate([0, 0, -0.1]) cylinder(d = idlerScrewDiameter + playLooseFit * 2, h = idlerwheel_piece_height + 0.2);
}

// Cutouts für das Idler-Wheel, in welche die Schraube, das Kugellager, sowie die Mutter platziert wird.
module idlerwheel_cutouts() render() {
	idlerwheel_screw();
	idlerwheel_track_teeth_cutouts();

	translate([0, 0, idlerwheel_piece_height - (idlerNutHeight + ballBearingHeight) + 2]) idlerwheel_bearing_cutouts();
}

// Simple repräsentation eines Idler-Rads
module idlerwheel_simple() render() {
	difference() {
		cylinder(r = smallWheelSize, h = idlerwheel_piece_height);

		idlerwheel_cutouts();
	}
}


idlerwheel_simple();


include <../Values/Values.scad>
use <../Tools.scad>
use <../Mechanics/Mechanics.scad>

// POSITIV für die Backplate, an der die Frontplate verbunden wird.
module backplate_plate_connector() {
	tag("positive") difference() {
		cylinder(d = idlerNutDiameter + playTightFit*2 + 2, h = idlerNutHeight);
		translate([0, 0, -0.1]) cylinder(d = idlerNutDiameter + playTightFit * 2, h = idlerNutHeight + 0.2, $fn = 6);
	}

	tag("negative", false) translate([0, 0, -50]) cylinder(d = idlerScrewDiameter + playTightFit*2, h = 100);
}

// CUTOUT für die Frontplate, da wo die Schrauben rein sollen.
module frontplate_plate_connector() {
	tag("negative") translate([0, 0, idlerScrewLength - plateTrackPlay*2 - trackWidth]) rotate([180, 0, 0]) idler_screw();
}

module backplate_plate_connectors()
	place_at_array(plateConnectors) backplate_plate_connector();
module frontplate_plate_connectors()
	place_at_array(plateConnectors) frontplate_plate_connector();

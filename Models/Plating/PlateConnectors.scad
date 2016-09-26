include <../Values/Values.scad>

use <../Tools.scad>
use <../Mechanics/Mechanics.scad>

// POSITIV für die Backplate, an der die Frontplate verbunden wird.
module backplate_plate_connector() {
	difference() {
		cylinder(d = plateConnectorScrewDiameter + playTightFit*2 + 2, h = backplateConnectorHeight);
		translate([0, 0, -0.1]) cylinder(d = plateConnectorScrewDiameter + playTightFit*2, h = backplateConnectorHeight + 1);
	}
}

// CUTOUT für die Frontplate, da wo die Schrauben rein sollen.
module frontplate_plate_connector() {
	translate([0, 0, idlerScrewLength - plateTrackPlay*2 - trackWidth]) rotate([180, 0, 0]) idler_screw();
}

module backplate_plate_connectors()
	place_at_array(plateConnectors) backplate_plate_connector();
module frontplate_plate_connectors()
	place_at_array(plateConnectors) frontplate_plate_connector();

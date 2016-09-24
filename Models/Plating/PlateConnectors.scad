include <../Values/Values.scad>

use <../Tools.scad>
use <../Mechanics/Mechanics.scad>


module backplate_plate_connectors() place_at_array(plateConnectors) {
	difference() {
		cylinder(d = plateConnectorScrewDiameter + playTightFit*2 + 2, h = backplateConnectorHeight);
		translate([0, 0, -0.1]) cylinder(d = plateConnectorScrewDiameter + playTightFit*2, h = backplateConnectorHeight + 1);
	}
}

module frontplate_plate_connectors() place_at_array(plateConnectors) {
	translate([0, 0, idlerScrewLength - plateTrackPlay*2 - trackWidth]) rotate([180, 0, 0]) idler_screw();
}

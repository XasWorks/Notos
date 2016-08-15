include <../Values/Values.scad>

use <../Tools.scad>

module backplate_plate_connectors() place_at_array(plateConnectors) {
	difference() {
		cylinder(d = 3 + playTightFit*2 + 2, h = backplateConnectorHeight);
		translate([0, 0, -0.1]) cylinder(d = 3 + playTightFit*2, h = backplateConnectorHeight + 1);
	}
}

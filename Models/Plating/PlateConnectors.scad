include <../Values/Values.scad>

use <../Tools.scad>

module backplate_plate_connectors() place_at_array(plateConnectors) {
	difference() {
		cylinder(d = plateConnectorScrewDiameter + playTightFit*2 + 2, h = backplateConnectorHeight);
		translate([0, 0, -0.1]) cylinder(d = plateConnectorScrewDiameter + playTightFit*2, h = backplateConnectorHeight + 1);
	}
}

module frontplate_plate_connectors() place_at_array(plateConnectors) {
	cylinder(d = plateConnectorScrewDiameter*2 + playLooseFit*2, h = 10);
	translate([0, 0, -plateConnectorScrewLength]) cylinder(d = plateConnectorScrewDiameter + playTightFit*2, h = plateConnectorScrewLength + 0.001);
}

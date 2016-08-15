include <../Values/Values.scad>

module place_at_connectorpos() {
	for(i = [0:len(plateConnectors) - 1]) translate(plateConnectors[i]) children();
}

module backplate_plate_connectors() place_at_connectorpos() {
	difference() {
		cylinder(d = 3 + playTightFit*2 + 2, h = backplateConnectorHeight);
		translate([0, 0, -0.1]) cylinder(d = 3 + playTightFit*2, h = backplateConnectorHeight + 1);
	}
}

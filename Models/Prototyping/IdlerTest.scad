
include <../Values/Values.scad>
use <../Tools.scad>

use <../Plating/PlateConnectors.scad>
use <../Plating/Backplate.scad>

screwDistance = 30;

screwPos = [[-screwDistance/2, 0], [screwDistance/2, 0]];

module basic_outline() {
	hull() {
		circle(r = smallWheelSize);
		place_at_array(screwPos) circle(d = idlerNutDiameter + playTightFit*2 + 2);
	}
}

module lower_plate() taggedDifference(["positive"], ["negative"], "neutral"){
	tag("positive")
	translate([0, 0, -backplateThickness + 0.001])
		linear_extrude(height = backplateThickness)
		basic_outline();

	place_at_array(screwPos) backplate_plate_connector();

	backplate_idlermount();
}

lower_plate();

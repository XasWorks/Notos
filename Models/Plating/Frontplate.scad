include <../Values/Values.scad>

use <../Tools.scad>

use <BasicPlating.scad>
use <PlateConnectors.scad>

module frontplate_basic() tag("positive") linear_extrude(height = frontplateThickness) plating_cut_lower() plating_outline();


// Distanzhalter für die Idlerwheels.
module frontplate_idler_mount() {
	tag("positive") translate([0, 0, -plateTrackPlay])
		cylinder(d = idlerScrewDiameter + playTightFit*2 + 1.5*2, h = plateTrackPlay + 0.001);

	tag("negative") translate([0, 0, -trackWidth - plateTrackPlay*2]) cylinder(d = idlerScrewDiameter + playLooseFit*2, h = idlerScrewLength + playLooseFit);
}

module frontplate_idler_mounts() place_at_idlerwheels() frontplate_idler_mount();

module frontplate() taggedDifference("positive", "negative", "neutral") {
	frontplate_basic();

	frontplate_plate_connectors();

	frontplate_idler_mounts();
}


frontplate();

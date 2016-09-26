include <../Values/Values.scad>

use <../Tools.scad>

use <BasicPlating.scad>
use <PlateConnectors.scad>

module frontplate_basic() linear_extrude(height = frontplateThickness) plating_cut_lower() plating_outline();

// Cutout für die Idlerwheel-Schrauben.
module frontplate_idler_screw_cut() {
	translate([0, 0, -trackWidth - plateTrackPlay*2]) cylinder(d = idlerScrewDiameter + playLooseFit*2, h = idlerScrewLength + playLooseFit);
}

// Distanzhalter für die Idlerwheels.
module frontplate_idler_spacer() {
	translate([0, 0, -plateTrackPlay]) difference() {
		cylinder(d = idlerScrewDiameter + playTightFit*2 + plateBearingRingThickness*2, h = plateTrackPlay + 0.001);
	}
}


module frontplate_screw_cuts()
	place_at_idlerwheels() frontplate_idler_screw_cut();
module frontplate_spacers()
	place_at_idlerwheels() frontplate_idler_spacer();


module frontplate_positives() {
	frontplate_basic();

	frontplate_spacers();
}
module frontplate_negatives() {
	frontplate_plate_connectors();

	frontplate_screw_cuts();
}


module frontplate() difference() { frontplate_positives(); frontplate_negatives(); }

frontplate();

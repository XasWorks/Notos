include <../Values/Values.scad>

use <../Tools.scad>

use <BasicPlating.scad>
use <PlateConnectors.scad>

module frontplate_basic() linear_extrude(height = frontplateThickness) plating_cut_lower() plating_outline();

module frontplate_screw_cuts() place_at_idlerwheels()
	translate([0, 0, -trackWidth - plateTrackPlay*2]) cylinder(d = idlerScrewDiameter + playLooseFit*2, h = idlerScrewLength);

module frontplate_spacers() place_at_idlerwheels() {
	translate([0, 0, -plateTrackPlay]) difference() {
		cylinder(d = idlerScrewDiameter + playTightFit*2 + plateBearingRingThickness*2, h = plateTrackPlay + 0.001);
	}
}

module frontplate_positives() {
	frontplate_basic();

	frontplate_spacers();
}

module frontplate_negatives() {
	translate([0, 0, plateConnectorScrewLength - (trackWidth + 2*plateTrackPlay)]) frontplate_plate_connectors();

	frontplate_screw_cuts();
}


module frontplate() difference() { frontplate_positives(); frontplate_negatives(); }

frontplate();

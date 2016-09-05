include <../Values/Values.scad>

use <../Tools.scad>

use <BasicPlating.scad>
use <PlateConnectors.scad>

module frontplate_basic() linear_extrude(height = frontplateThickness) plating_cut_lower() plating_outline();

module frontplate_screw_cuts() place_at_idlerwheels()
	translate([0, 0, -trackWidth - plateTrackPlay*2]) cylinder(d = idlerScrewDiameter + playTightFit*2, h = idlerScrewLength);

module frontplate_nut_mounts() place_at_idlerwheels() {
	translate([0, 0, -idlerNutHeight + playLooseFit*2]) difference() {
		cylinder(d = idlerNutDiameter + idlerNutMountThickness + playTightFit*2, h = idlerNutHeight - playLooseFit*2 + 0.01);
		translate([0, 0, -0.001]) cylinder(d = idlerNutDiameter + playTightFit*2, h = idlerNutHeight + 0.001);
	}
}

module frontplate_positives() {
	frontplate_basic();

	frontplate_nut_mounts();
}

module frontplate_negatives() {
	translate([0, 0, plateConnectorScrewLength - (trackWidth + 2*plateTrackPlay)]) frontplate_plate_connectors();

	frontplate_screw_cuts();
}


module frontplate() difference() { frontplate_positives(); frontplate_negatives(); }

frontplate();

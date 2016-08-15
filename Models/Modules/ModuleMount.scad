include <../Values/Values.scad>


module place_at_mountpos() {
	for(i=[0:len(modulesPositions) - 1]) translate(modulesPositions[i]) children();
}

module module_screw_outline() {
	translate([-modulesConnectorScrewDistance/2, 0]) circle(d = 3*2 + playTightFit*2 + (1*2));
	translate([modulesConnectorScrewDistance/2, 0]) circle(d = 3*2 + playTightFit*2 + (1*2));
}
module module_screw_outlines() {
	place_at_mountpos() module_screw_outline();
}

module module_screw_cutout() {
	translate([0, 0, -modulesScrewHeadCutDepth]) cylinder(d = modulesScrewDiameter * 2 + playLooseFit*2, h = 5);
	translate([0, 0, -20]) cylinder(d = modulesScrewDiameter + playTightFit*2, h = 30);
}
module modules_screw_cutouts() place_at_mountpos() {
	translate([-modulesConnectorScrewDistance/2, 0]) module_screw_cutout();
	translate([modulesConnectorScrewDistance/2, 0]) module_screw_cutout();
}

module module_outline() {
	translate([-modulesWidth/2, 0]) square([modulesWidth, 30]);
}
module module_outlines() {
	place_at_mountpos() module_outline();
}

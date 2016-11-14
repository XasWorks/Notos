include <../Values/Values.scad>

wallThickness = 1.36;

objectHeight = trackWidth + 2*plateTrackPlay - idlerNutHeight - playLooseFit;
difference() {
	cylinder(d = idlerScrewDiameter + wallThickness*2 + playLooseFit *2, h = objectHeight);
	translate([0, 0, -0.1]) cylinder(d = idlerScrewDiameter + playLooseFit*2, h = objectHeight + 0.2);
}


include <../Values/Values.scad>

module motor_screws() {
	for (i = [0:90:360]) rotate([0, 0, i]) translate([motorMountscrewsDistance/2, motorMountscrewsDistance/2, 0])
	cylinder(d = 3 + playLooseFit * 2, h = motorBackplateHoleHeight + 2);
}

module motor_basic() {
	mSize = motorSizeWidth + playLooseFit * 2;
	translate([-mSize/2, -mSize/2, -10]) cube([mSize, mSize, 10]);
}

module motor_bphole() {
	cylinder(d = motorBackplateHoleDiameter + playLooseFit * 2, h = motorBackplateHoleHeight + 0.1);
}

module motor_axis() {
	difference() {
		cylinder(d = motorAxisFullDiam + playTightFit * 2, h = motorAxisFullLength + playLooseFit);

		translate([motorAxisFullDiam/2 - (motorAxisFullDiam - motorAxisIndentDiam) - playTightFit, -motorAxisFullDiam/2, motorAxisFullLength - motorAxisIndentLength])
			cube([motorAxisFullDiam, motorAxisFullDiam, motorAxisIndentLength + 0.1]);
	}
}

module motor_cutouts(backplate_aligned = true) render(convexity = 5) {
	translate([0, 0, (backplate_aligned) ? -backplateThickness : 0]) {
		motor_axis();
		motor_screws();
		motor_basic();
		motor_bphole();
	}
}

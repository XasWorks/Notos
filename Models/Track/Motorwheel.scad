include <../Values/Values.scad>

use <../Mechanics/Motor.scad>
use <Track.scad>

module motorwheel_basic() {
	cylinder(r = motorWheelSize, h = trackWidth - 0.002);
}

module motorwheel_axisCutout() {
	translate([0, 0, -backplateThickness - plateTrackPlay]) motor_axis();
}

module motorwheel_trackCutout() {
	translate([0, 0, -0.001]) track(motorWheelSize + 0.001, clearance_offset = true);
}

module motorwheel() render() {
	difference() {
		motorwheel_basic();
		motorwheel_axisCutout();
		motorwheel_trackCutout();
	}
}



motorwheel();

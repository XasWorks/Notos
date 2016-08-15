include <MCAD/stepper.scad>

use <TagSystem/Tagging.scad>
include <../Values/Values.scad>

use <../Track/Idler.scad>
use <../Track/Motorwheel.scad>

use <../Mechanics/Mechanics.scad>

use <../Plating/Backplate.scad>
use <../Plating/BasicPlating.scad>

use <../Modules/ModuleMount.scad>

module wheel() {
		translate([0, 0, plateTrackPlay])
		translate([0, 0, trackWidth/2]) {
			mirror([0, 0, 1]) idlerwheel();
			idlerwheel();
		}

	color("grey") idler_screw(true);
}

module motor_wheel() {
	translate([0, 0, plateTrackPlay]) motorwheel();
}

module motor_display() {
	translate(wheelPositions[0]) translate([0, 0, 1 - backplateThickness]) %motor(model=Nema14, size=NemaLengthLong, orientation=[180, 0, 0]);
}

module wheels() {
	if(len(wheelPositions) >= 2) {

		motor_display();

		translate(wheelPositions[0]) motor_wheel();

		place_at_idlerwheels() wheel();
	}
}

backplate();
wheels();

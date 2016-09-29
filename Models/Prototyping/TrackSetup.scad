include <MCAD/stepper.scad>

use <../Tools.scad>
include <../Values/Values.scad>

use <../Track/Idler.scad>
use <../Track/Motorwheel.scad>

use <../Mechanics/Mechanics.scad>

use <../Plating/Backplate.scad>
use <../Plating/BasicPlating.scad>
use <../Plating/Frontplate.scad>

use <../Modules/ModuleMount.scad>
use <../Modules/ModuleAdapter.scad>

module wheel() {
	translate([0, 0, plateTrackPlay]) bearingless_idlerwheel();
	color("grey") %idler_screw(true);
}

module motor_wheel() {
	translate([0, 0, plateTrackPlay]) motorwheel();
}

module motor_display() {
	translate(wheelPositions[0]) translate([0, 0, 1 - backplateThickness]) motor(model=Nema14, size=NemaLengthLong, orientation=[180, 0, 0]);
}

module wheels() {
	if(len(wheelPositions) >= 2) {

		motor_display();

		translate(wheelPositions[0]) motor_wheel();

		place_at_idlerwheels() wheel();
	}
}

module track_assembly() translate([0, -backplateThickness - modulesLength/2, 0]) rotate([90, 0, 0]) {
	translate([0, 0, trackWidth + plateTrackPlay*2]) frontplate();
	backplate();
	wheels();
}

module track_drive() {
	track_assembly();
	mirror([0, 1, 0]) track_assembly();
}

module modules_adapters() {
	for(i = modulesPositions) translate([i[0], 0, i[1] - modulesAdapterThickness/2]) rotate([0, 0, 90]) mount_connector();
}

modules_adapters();
track_drive();

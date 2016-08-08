include <MCAD/stepper.scad>

use <TagSystem/Tagging.scad>
include <../Values/Values.scad>



module wheel() {
	circle(r = smallWheelSize);
}

module motor_wheel() {
	circle(r = motorWheelSize);
}

module motor_display() {
	translate(wheelPositions[0]) %motor(model=Nema14, size=NemaLengthLong, orientation=[180, 0, 0]);
}

module wheels() {
	if(len(wheelPositions) >= 2) {

		motor_display();

		translate(wheelPositions[0]) motor_wheel();

		for( i = [1: len(wheelPositions) - 1]) {
			translate(wheelPositions[i]) wheel();
		}
	}
}

wheels();

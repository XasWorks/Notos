include <MCAD/stepper.scad>

use <TagSystem/Tagging.scad>
include <../Values/Values.scad>



module wheel() {
	circle(r = smallWheelSize);
}

module motorWheel() {
	circle(r = motorWheelSize);
}

module motor_display() {
	translate(wheelPositions[0]) %motor(model=Nema14, size=NemaLengthLong, pos=[0, 0, 1], orientation=[180, 0, 0]);
}

module wheels() {
	if(len(wheelPositions) >= 2) {

		motor_display();

		translate(wheelPositions[0]) motorWheel();

		for( i = [1: len(wheelPositions) - 1]) {
			translate(wheelPositions[i]) wheel();
		}
	}
}

wheels();

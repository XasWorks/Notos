include <../Values/Values.scad>


module place_at_idlerwheels() {
	if(len(wheelPositions) >= 2) {

		for( i = [1: len(wheelPositions) - 1]) {
			translate(wheelPositions[i]) children();
		}
	}
}

module plating_outline() {
	hull() {
		translate(wheelPositions[0]) circle(r = motorWheelSize);
		place_at_idlerwheels() circle(r = smallWheelSize);
	}
}

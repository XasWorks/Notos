use <TagSystem/Tagging.scad>
include <../Values.scad>


module wheel() {
	circle(r = smallWheelSize);
}

module motorWheel() {
	circle(r = motorWheelSize);
}

module wheels() {
	if(len(wheelPositions) >= 2) {
		
		translate(wheelPositions[0]) motorWheel();
		
		for( i = [1: len(wheelPositions) - 1]) {
			translate(wheelPositions[i]) wheel();
		}
	}
}

wheels();
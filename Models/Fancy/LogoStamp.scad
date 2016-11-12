
stampBaseHeight = 1;
stampShapeHeight = 1;

stampGripWidth = 1.5;
stampGripLength = 20;
stampGripHeight = 20;

module stamp_shape() {
	resize([40, 0, stampShapeHeight], auto=true) 
	import("Logo.stl");
}

module stamp_base() {
	
	linear_extrude(height = stampBaseHeight)
	hull() projection() stamp_shape();
}

module stamp_grip() {
	stamp_base();
	translate([0, 0, stampGripHeight/2 + stampBaseHeight - 0.01]) 
		cube([stampGripLength, stampGripWidth, stampGripHeight], center=true);
}

module stamp() {
	translate([0, 0, stampBaseHeight]) stamp_shape();
	stamp_base();
}

stamp_grip();
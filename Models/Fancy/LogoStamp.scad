
stampBaseHeight = 1;
stampShapeHeight = 1;

module stamp_shape() {
	resize([40, 0, stampShapeHeight], auto=true) 
	import("Logo.stl");
}

module stamp_base() {
	
	linear_extrude(height = stampBaseHeight)
	hull() projection() stamp_shape();
}

module stamp() {
	translate([0, 0, stampBaseHeight]) stamp_shape();
	stamp_base();
}

stamp();
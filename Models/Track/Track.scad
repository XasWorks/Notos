include <../Values/Values.scad>


module track_basicring(r = 10) render(convexity = 3) {
	difference() {
		cylinder(r = r + trackThickness, h = trackWidth);
		translate([0, 0, -0.1]) cylinder(r = r, h = trackWidth + 0.2);
	}
}

module track_tooth() {
	linear_extrude(height = trackWidth) {
		polygon([	[trackTeethBaseWidth/2, 0],
						[trackTeethTopWidth/2, -trackTeethHeight],
						[-trackTeethTopWidth/2, -trackTeethHeight],
						[-trackTeethBaseWidth/2, 0]]);
	}
}

module track_teeth_noslip(r = 10) {
	rotate_extrude() {
		polygon([	[r - trackTeethHeight - 0.01, trackTeethNoslipTop/2],
						[r - trackTeethHeight - 0.01, -trackTeethNoslipTop/2],
						[r + 0.01, -trackTeethNoslipBase/2],
						[r + 0.01, trackTeethNoslipBase/2]]);
	}
}

module track_teeth(r = 10) {
	trackCircumference = 6.28318 * r;
	teethNum = floor(trackCircumference / trackTeethSpacing);

	intersection() {
		for(i=[0:360/teethNum:360]) rotate([0, 0, i]) render() difference() {
			translate([0, r, 0]) track_tooth();
			translate([0, 0, trackWidth/2]) track_teeth_noslip(r);
		}

		cylinder(r = r + 0.001, h = trackWidth);
	}
}

module track(r = 10) {
	track_teeth(r);
	track_basicring(r);
}

track(50);

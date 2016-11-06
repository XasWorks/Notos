include <../Values/Values.scad>


module track_basicring(r = 10) render(convexity = 3) {
	difference() {
		cylinder(r = r + trackThickness, h = trackWidth);
		translate([0, 0, -0.1]) cylinder(r = r, h = trackWidth + 0.2);
	}
}

module track_tooth() {
	teethOffset = $teeth_use_offset ? playLooseFit : 0;

	trackTeethBaseWidth = trackTeethBaseWidth + teethOffset * 2;
	trackTeethTopWidth = trackTeethTopWidth + teethOffset * 2;
	trackTeethHeight = trackTeethHeight + teethOffset;

	linear_extrude(height = trackWidth) {
		polygon([	[trackTeethBaseWidth/2, 0],
						[trackTeethTopWidth/2, -trackTeethHeight],
						[-trackTeethTopWidth/2, -trackTeethHeight],
						[-trackTeethBaseWidth/2, 0]]);
	}
}

module track_teeth_noslip(r = 10) {
	teethOffset = $teeth_use_offset ? playLooseFit : 0;

	trackTeethHeight = trackTeethHeight + teethOffset;

	rotate_extrude() {
		polygon([	[r - trackTeethHeight - 0.01, trackTeethNoslipTop/2],
						[r - trackTeethHeight - 0.01, -trackTeethNoslipTop/2],
						[r + 0.01, -trackTeethNoslipBase/2],
						[r + 0.01, trackTeethNoslipBase/2]]);
	}
}

module track_teeth(r = 10, tRadius = -1) {
	tRadius = (tRadius < 0) ? r : tRadius;
	
	trackCircumference = 6.28318 * tRadius;
	teethNum = floor(trackCircumference / trackTeethSpacing);

	intersection() {
		for(i=[0:360/teethNum:360]) rotate([0, 0, i]) render() difference() {
			translate([0, r, 0]) track_tooth();
			translate([0, 0, trackWidth/2]) track_teeth_noslip(r);
		}

		cylinder(r = r + 0.001, h = trackWidth);
	}
}

module track(r = 10, rShrink = 0, clearance_offset = false) {
	$teeth_use_offset = clearance_offset;

	track_teeth(r - rShrink, r);
	track_basicring(r - rShrink);
}

track(48.556, 3/6.28318);


include <../Values/Values.scad>

sliceHeight = 1;

coverX = 5.5;
coverY = 7;

coverShiftY = 9;

coverPositions = [[1, 0], [1, 7], [1.5, 15], [1.5, 23]];

module LFS_ScrewHole() {
	tag("positive") cylinder(d = 7.5, h = sliceHeight);
	tag("negative") translate([0, 0, -0.1]) cylinder(r = 1.8, h = sliceHeight + 0.2);
}

module LFS_coverSlice(s, h) {
	translate([0, coverShiftY, h]) linear_extrude(height = sliceHeight) {
		tag("negative") square([coverX * s, coverY * s], true);
		tag("positive") square([coverX * s+ 2, coverY * s+ 2], true);
	}
}

module LFS_cover() taggedDifference("positive","negative") {
	tag("positive") hull() showOnly("positive") {
		LFS_ScrewHole();
		LFS_coverSlice(1, 0);
	}
	LFS_coverSlice(1, 0);
	LFS_ScrewHole();

	for(x = [1:len(coverPositions) - 1]) {
		hull() {
			LFS_coverSlice(coverPositions[x][0], coverPositions[x][1]);
			LFS_coverSlice(coverPositions[x-1][0], coverPositions[x-1][1]);
		}
	}
}

LFS_cover();

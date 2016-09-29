
include <../Values/Values.scad>
use <../Tools.scad>

mountConnectorPos = [[0, -modulesConnectorScrewDistance/2, 0], [0, modulesConnectorScrewDistance/2, 0]];

mUConX = modulesLength/2 	- modulesScrewInwardsShift;
mUConY = modulesWidth/2 	- modulesScrewInwardsShift;
mountUpConnectorPos = [	[mUConX, mUConY],
								[mUConX, -mUConY],
								[-mUConX, mUConY],
								[-mUConX, -mUConY]];

module mount_connector_block() {
	wThickness = modulesAdapterBlockWallThickness;

	tScrewDiameter = modulesScrewDiameter + playTightFit*2;

	blockWidth = tScrewDiameter + wThickness*2;
	blockGirth = modulesAdapterBlockGirth;
	blockHeight = blockWidth;

	tag("positive") translate([0, -blockWidth/2, 0])	cube([blockGirth, blockWidth, blockHeight]);
	tag("negative") translate([-0.05, 0, blockHeight/2]) rotate([0, 90, 0]) cylinder(d = tScrewDiameter, h = blockGirth + 10);
}
module mount_connector_block_set() {
	place_at_array(mountConnectorPos) translate([0, 0, modulesAdapterBlockLift]) mount_connector_block();
}
module mount_connector_blocks() {
	translate([-modulesLength/2, 0, 0]) mount_connector_block_set();
	translate([modulesLength/2 - modulesAdapterBlockGirth, 0, 0]) mount_connector_block_set();
}

module mount_connector_upwards() {
	tScrewDiameter = modulesScrewDiameter + playTightFit*2;

	tag("negative") translate([0, 0, -0.01])
		cylinder(d = tScrewDiameter, h = 100);

	tag("positive") cylinder(d = modulesScrewInwardsShift, h = modulesVertConnectorHeight);
}
module mount_connectors_upwards() {
	place_at_array(mountUpConnectorPos) mount_connector_upwards();
}

module mount_connector_basis() {
	edgeRounding = modulesScrewInwardsShift;

	tag("positive") linear_extrude(height = modulesAdapterThickness)
		offset(r = edgeRounding) offset(r = -edgeRounding)
		translate([-modulesLength/2, -modulesWidth/2]) square([modulesLength, modulesWidth]);
}

module mount_connector() {
	taggedDifference("positive", "negative", "neutral") {
		mount_connector_basis();
		mount_connectors_upwards();
		mount_connector_blocks();
	}
}

mount_connector();


include <../Values/Values.scad>
use <../Tools.scad>

mountConnectorPos = [[0, -modulesConnectorScrewDistance/2, 0], [0, modulesConnectorScrewDistance/2, 0]];

mUConX = modulesLength/2 	- modulesScrewInwardsShift;
mUConY = modulesWidth/2 	- modulesScrewInwardsShift;
mountUpConnectorPos = [	[mUConX, mUConY],
								[mUConX, -mUConY],
								[-mUConX, mUConY],
								[-mUConX, -mUConY]];

module smoothCube(lX, lY, r, h) {
	cubeX = lX - r*2;
	cubeY = lY - r*2;

	linear_extrude(height = h) {
		offset(r = r) {
			translate([-cubeX/2, -cubeY/2]) square([cubeX, cubeY]);
		}
	}
}

module module_adapter_block() {
	wThickness = modulesAdapterBlockWallThickness;

	tScrewDiameter = modulesScrewDiameter + playTightFit*2;

	sleekMode = tScrewDiameter <= modulesAdapterThickness;

	blockWidth = tScrewDiameter + wThickness*2;
	blockGirth = modulesAdapterBlockGirth;
	blockHeight = sleekMode ? modulesAdapterThickness : blockWidth ;

	translate([0, 0, sleekMode ? 0 : modulesAdapterBlockLift]) {
		tag("positive") translate([0, -blockWidth/2, 0])	cube([blockGirth, blockWidth, blockHeight]);
		tag("negative") translate([-0.05, 0, blockHeight/2]) rotate([0, 90, 0]) cylinder(d = tScrewDiameter, h = blockGirth + 10);
	}
}
module module_adapter_block_set() {
	place_at_array(mountConnectorPos) module_adapter_block();
}
module module_adapter_blocks() {
	translate([-modulesLength/2, 0, 0]) module_adapter_block_set();
	translate([modulesLength/2 - modulesAdapterBlockGirth, 0, 0]) module_adapter_block_set();
}

module module_adapter_upwards() {
	tScrewDiameter = modulesScrewDiameter + playTightFit*2;

	tag("negative") translate([0, 0, -0.01])
		cylinder(d = tScrewDiameter, h = 100);

	tag(["positive", "up_connectors"]) cylinder(r = modulesScrewInwardsShift, h = modulesVertConnectorHeight);
}
module module_adapters_upwards() {
	place_at_array(mountUpConnectorPos) module_adapter_upwards();
}

module module_adapter_basis() {
	tag("positive") smoothCube(modulesLength, modulesWidth, modulesScrewInwardsShift, modulesAdapterThickness);
}

module module_adapter() {
	taggedDifference("positive", "negative", "neutral") {
		module_adapter_basis();
		module_adapters_upwards();
		module_adapter_blocks();
	}
}

module_adapter();

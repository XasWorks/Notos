
cWidth = 60;

difference() {
	cube([cWidth, cWidth, 0.5]);
	translate([cWidth/2, cWidth/2, -0.1]) resize([40, 0, 1], auto=true) import("Logo.stl");
}
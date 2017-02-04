$fs = 0.8;

cyDiam = 3.2;
cyHeight = 18;

linear_extrude(height = cyHeight) 
difference() {
	circle(r = cyDiam/2 + 0.9);
	circle(r = cyDiam/2);
}
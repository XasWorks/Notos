
$fs = 1;
$fa = 7;

// Mechanik-Werte
include <Mechanic.scad>

// Idler-Räder-Werte
  smallWheelSize = 11; // Größe der kleinen Räder

// Ketten-Bestimmende Werte
  motorWheelSize = 15; // Größe des Motor-Antriebsrades

  wheelPositions = [[0, 28], [-40, smallWheelSize], [-57, 32], [45, smallWheelSize]];   // Array mit den einzelnen Positionen der Räder (erster Eintrag bestimmt den Motor)

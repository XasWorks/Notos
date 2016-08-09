
// Werte für Idler-Räder
smallWheelSize = 10;	// Radius des Idler-Rads

// Werte für das Motor-Rad
motorWheelSize = 15; // Größe des Motor-Antriebsrades

// Werte für die Kette selbst
	floorWheelNum = 4; 			// Anzahl der Räder welche auf dem Boden aufliegen.
	floorWheelStartX 	= -45;	// Anfang der Boden-Räder
	floorWheelEndX 		=	45; 	// Ende der Boden-Räder
	function floorWheels() = [ for(x = [floorWheelStartX:(floorWheelEndX - floorWheelStartX)/(floorWheelNum-1):floorWheelEndX]) [x, smallWheelSize]];

	echo(len(floorWheels()));

	// Array mit den einzelnen Positionen der Räder (erster Eintrag bestimmt den Motor)
	wheelPositions = concat([[0, 35], [-57, 32]], floorWheels());

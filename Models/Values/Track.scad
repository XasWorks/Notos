
// Werte für Idler-Räder
smallWheelSize = 10;	// Radius des Idler-Rads

// Werte für das Motor-Rad
motorWheelSize = 15; // Größe des Motor-Antriebsrades

// Breite der Kette
trackWidth = 20;

// Werte für die Verzahnung der Kette
	trackTeethHeight = 2;		// Höhe der Verzahnung
	trackTeethNoslip = 5; 		// Wie weit in der Mitte der Kette die Verzahnung entfernt werden soll, um sie auf den Rädern zu halten.


// Werte für die Kette selbst
	floorWheelNum = 4; 			// Anzahl der Räder welche auf dem Boden aufliegen.
	floorWheelStartX 	= -45;	// Anfang der Boden-Räder
	floorWheelEndX 		=	45; 	// Ende der Boden-Räder
	function floorWheels() = [ for(x = [floorWheelStartX:(floorWheelEndX - floorWheelStartX)/(floorWheelNum-1):floorWheelEndX]) [x, smallWheelSize]];

	// Array mit den einzelnen Positionen der Räder (erster Eintrag bestimmt den Motor)
	wheelPositions = concat([[0, 35], [-57, 32]], floorWheels());

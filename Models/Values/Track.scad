
// Werte für Idler-Räder
idlerwheelSize = 10;	// Radius des Idler-Rads
idlerwheelScrewBushingHeight 	= 2;
idlerwheelScrewExtraSpacing 	= 0.5;
// Werte für das Motor-Rad
motorWheelSize = 15; // Größe des Motor-Antriebsrades

// Größen der Kette
	trackWidth = 20;
	trackThickness = 1.5;

// Werte für die Verzahnung der Kette
	trackTeethHeight = 1.5;		// Höhe der Verzahnung
	trackTeethBaseWidth = 1.5;	// Breite eines Zahnes
	trackTeethTopWidth = 0.6;

	trackTeethSpacing = (idlerwheelSize * 6.2831) / 10;		// Mit welchem Abstand sollen die Zähne vorkommen?

	trackTeethNoslipBase = 3; 	// Wie weit in der Mitte der Kette die Verzahnung entfernt werden soll, um sie auf den Rädern zu halten.
	trackTeethNoslipTop = 5;


// Werte für die Kette selbst
	floorWheelNum = 4; 			// Anzahl der Räder welche auf dem Boden aufliegen.
	floorWheelStartX 	= -45;	// Anfang der Boden-Räder
	floorWheelEndX 		=	45; 	// Ende der Boden-Räder
	function floorWheels() = [ for(x = [floorWheelStartX:(floorWheelEndX - floorWheelStartX)/(floorWheelNum-1):floorWheelEndX]) [x, idlerwheelSize]];

	// Position des Motors
	motorWheelPosition = [0, 40];

	firstWheelY 	= idlerwheelSize*3;
	firstWheelX 	= floorWheelStartX - (firstWheelY - idlerwheelSize);
	firstWheelPosition = [firstWheelX, firstWheelY];

	// Array mit den einzelnen Positionen der Räder (erster Eintrag bestimmt den Motor)
	wheelPositions = concat([motorWheelPosition, firstWheelPosition], floorWheels());

	// Zusätzliche Punkte, mit welchen die Backplate an einigen Stellen vergrößert werden kann.
	backplateExtraSpots = [wheelPositions[0] + [17.5, 17.5], wheelPositions[0] + [-17.5, 17.5]];


echo(wheelPositions);

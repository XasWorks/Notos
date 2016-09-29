
// Distanz der zwei Anbringungsschrauben für eine Modul-Platte
modulesConnectorScrewDistance = 22.5;

// Größenangaben der Module
modulesWidth = 40;
modulesLength = 70;

// Positionen der einzelnen Module
lowerModulesHeight = 16;
modulesPositions = [[0, 40 + 37/2 + 3], [-42, lowerModulesHeight], [42, lowerModulesHeight]];

// Radius der Schraube
modulesScrewDiameter = 3;
// Wie tief soll für den Kopf platz gemacht werden?
modulesScrewHeadCutDepth = 1.7;

// --- Variablen des Adapter-Blocks ---

modulesAdapterThickness = 3.5;

// Variablen des Verbinder-Blocks
modulesAdapterBlockGirth = 5;
modulesAdapterBlockWallThickness = 1.5;
modulesAdapterBlockLift = modulesAdapterThickness - modulesAdapterBlockWallThickness;

// Variablen der vertikalen Verbinder
modulesScrewInwardsShift = 3; // Wie weit die Verbinder-Schrauben "nach innen" bewegt werden sollen.
modulesVertConnectorHeight =
	modulesAdapterThickness; // Höhe des Verbinders
modulesVertConnectorWallThickness = 1;

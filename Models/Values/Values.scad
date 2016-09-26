
use <TagSystem/Tagging.scad>

$fs = 0.8;
$fa = 7;

// Spielraum-Werte für den Drucker.
playTightFit = 0.09;
playLooseFit = 0.35;

// Mechanik-Werte
include <Mechanic.scad>

// Idler-Räder-Werte
include <Track.scad>

// Schrittmotor-Werte
include <Motor.scad>

// Werte für die Außenplatten
include <Plating.scad>

// Modul-Werte
include <Modules.scad>

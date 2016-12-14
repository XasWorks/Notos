/*
 * main.c
 *
 *  Created on: Oct 9, 2016
 *      Author: xasin
 */

#include "Localcode/Robot.h"

using namespace Robot;
using Communication::Pattern;

// Eine "ISR"-Funktion ist eine Funktion, welche zu bestimmten Zeitpunkten automatisch aufgerufen wird.
// In dieserm Fall handelt es sich um die "TIMER1 - CompareInterrupt A" ISR. D.h. der Timer, hier aufgerufen alle 0.2ms
ISR(TIMER1_COMPA_vect) {
	ISR1();
}

// Diese ISR wird aufgerufen, wenn der ADC mit einer Umwandlung fertig ist. An sich ist es nur eine Hardware-Sache, also muss es nicht direkt verstanden werden.
ISR(ADC_vect) {
	ISRADC();
}


// Die main-Methode des Roboters. Hier steht alles /wirklich/ wichtige drinnen, nämlich der eigentliche Programmcode.
int main() {

	switch(init()) {
	case powerupButton:
		Led.setModes(0, 0, Pattern::slowblink);
		while(true) {}
	break;

	case noVoltage:
		Led.setModes(0, 1, 0);
		while(true) {}
	break;

	case noButton:
		Led.setModes(0, 0b101, 0);
		while(true) {}
	break;

	case startButton:
		break;
	}

	setMotors(true);
	Led.setModes(Pattern::flash, 0, 0);

	_delay_ms(1000);

	Motor.setSpeed(350);
	Motor.setRotationSpeed(0);

	Motor.continuousMode();

	// Dauerschleife mit Motor-Test-Programm.
	while(1) {
	}

	return 1;
}

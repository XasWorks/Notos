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

	init();

	Led.setModes(0b1010101, 0b11001100, 0b11110000);

	_delay_ms(1000);

	Motor.setSpeed(0);
	Motor.setRotationSpeed(360);
	Motor.continuousMode();

	// Dauerschleife mit Motor-Test-Programm.
	while(1) {
		Motor.setRotationSpeed(LSensor.lineOffset * 360.0 / 127);
		switch(LSensor.lineStatus) {
		case LF::OK:
			Led.setModes(Pattern::off, Pattern::on, Pattern::off);
		break;

		case LF::LOST:
			Led.setModes(Pattern::flash, 0, 0);
		break;

		default:
			Led.setModes(Pattern::off, 0, Pattern::slowblink);
		break;
		}
	}

	return 1;
}

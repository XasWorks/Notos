/*
 * main.c
 *
 *  Created on: Oct 9, 2016
 *      Author: xasin
 */

#include "main.h"
#include "Localcode/States/USB.h"
#include "Localcode/States/LineFollow.h"

using namespace Robot;
using Communication::Pattern;

void (*stateFunction)();

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

	case noButton:
	case noVoltage:
		stateFunction = &State::USB::simpleDebug;
	break;

	case lowBattery:
		Led.setModes(0b101101011, 0, 0);
		while(true) {}
	break;

	case startButton:
		setMotors(true);
		stateFunction = &State::LineFollow::simpleLF;
		break;
	}

	// Dauerschleife mit Motor-Test-Programm.
	while(1) {
		_delay_ms(10);
		if(stateFunction != 0)
			stateFunction();
	}

	return 1;
}

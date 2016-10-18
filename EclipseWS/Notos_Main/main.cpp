/*
 * main.c
 *
 *  Created on: Oct 9, 2016
 *      Author: xasin
 */


// Die folgenden Bibliotheken sind Standard-Header-Dateien, um den Microcontroller nutzen zu können.
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Die "Timer" Bilbiothek erlaubt eine vereinfachte Nutzung der eingebauten Timer des Mega32
#include "AVR/TIMER/Timer1.h"
// Die "PrimitiveStepper" Bibliothek erlaubt eine einfache Ansteuerung der Schrittmotoren - sie sollte nur für tests genutzt werden!
#include "AVR/Actuators/Steppers/PrimitiveStepper.h"
// Die ADC-Bibliothek erlaubt einfachen Zugriff auf den Analog-Digital-Wandler, vergleichbar mit der Arduino "AnalogRead" Funktion
#include "AVR/ADC/ADC_Lib.h"

// Instanzierung der zwei Test-Schrittmotoren
PrimitiveStepper test1 = PrimitiveStepper(&PORTB, 0, 2, 5000);
PrimitiveStepper test2 = PrimitiveStepper(&PORTB, 1, 2, 5000);


// Diese Funtkion liest mithilfe des ADC die Batterie-Spannung aus, und vergleicht sie mit einem Prüfwert, um sicher zu stellen dass die Batterie nicht leer ist.
// Grade jetzt werden dementsprechend einfach nur die Motoren aus oder an geschaltet.
void check_voltage() {
	uint16_t voltage = ADC_Lib::lastResult;
	if(voltage > 495)
		PORTB &= ~(1<< 3);
	else
		PORTB |= (1<< 3);
}


uint16_t isrPresc = 0;

// Eine "ISR"-Funktion ist eine Funktion, welche zu bestimmten Zeitpunkten automatisch aufgerufen wird.
// In dieserm Fall handelt es sich um die "TIMER1 - CompareInterrupt A" ISR. D.h. der Timer, hier aufgerufen alle 0.2ms
ISR(TIMER1_COMPA_vect) {

	// Aufruf der Schrittmotoren, um sich zu updaten.
	test1.update();
	test2.update();

	// "Prescaler", d.h. dass die nachfolgenden Funktionen nicht immer, sondern in längeren Abständen aufgerufen werden.
	if(--isrPresc == 0) {
		ADC_Lib::start_measurement(7);
		isrPresc = 500;
	}
}

// Diese ISR wird aufgerufen, wenn der ADC mit einer Umwandlung fertig ist. An sich ist es nur eine Hardware-Sache, also muss es nicht direkt verstanden werden.
ISR(ADC_vect) {
	ADC_Lib::update();

	if(ADC_Lib::measuredPin == 7)
		check_voltage();
}

// Die main-Methode des Roboters. Hier steht alles /wirklich/ wichtige drinnen, nämlich der eigentliche Programmcode.
int main() {

	// Initialisierung der Hardware-Pins (ähnlich des "pinMode" des Arduino)
	DDRB |= (0b1111);
	PORTB |= (0b10000);
	DDRC |= (0b11100);

	PORTB |= 0b100;

	// Initialisierung des ADC
	ADC_Lib::init(ADC_PRSC_128, ADC_REF_AREF);

	// Initialisierung des Timer1 auf CTC (Clear Timer on Compare)-Modus. D.h. ganz normaler Timer Modus.
	Timer1::set_prescaler(TIMER1_PRESC_64);
	Timer1::set_mode(TIMER1_MODE_CTC);
	// Setzen der Dauer des Timer auf 0.2ms, d.h. also dass die TIMER1_COMPA_vect ISR mit 5000kHz aufgerufen wird.
	Timer1::set_OCR1A(50 - 1);
	sei();

	// Setzten der Motor-Geschwindigkeit in Schritte pro Sekunde
	test1.setSpeed(800);
	test2.setSpeed(800);

	// Dauerschleife mit Motor-Test-Programm.
	while(1) {

		// "move" bewegt die Motoren um die angegebene Anzahl Schritte (800 sind hierbei eine halbe Umdrehung)
		test1.move(800);
		test2.move(800);

		// "flush" wartet darauf dass der Motor aufhört sich zu bewegen
		test1.flush();

		test1.move(800);
		test2.move(-800);

		test1.flush();

		test1.move(-800);
		test2.move(800);

		test1.flush();
	}

	return 1;
}

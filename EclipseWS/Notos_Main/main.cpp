/*
 * main.c
 *
 *  Created on: Oct 9, 2016
 *      Author: xasin
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "AVR/TIMER/Timer1.h"
#include "AVR/Actuators/Steppers/PrimitiveStepper.h"

PrimitiveStepper test1 = PrimitiveStepper(&PORTB, 0, 2, 5000);
PrimitiveStepper test2 = PrimitiveStepper(&PORTB, 1, 2, 5000);

ISR(TIMER1_COMPA_vect) {
	test1.update();
	test2.update();
}

int main() {

	DDRB |= (0b1111);
	PORTB |= (0b10000);
	DDRC |= (0b11100);

	PORTB |= 0b100;

	Timer1::set_prescaler(TIMER1_PRESC_64);
	Timer1::set_mode(TIMER1_MODE_CTC);
	Timer1::set_OCR1A(50 - 1);
	sei();

	test1.setSpeed(800);
	test2.setSpeed(800);

	while(1) {
		test1.move(800);
		test2.move(800);

		test1.flush();

		test1.move(800);
		test2.move(-800);

		test1.flush();

		test1.move(-800);
		test2.move(800);

		test1.flush();
	}

	while(1) {}
	return 1;
}



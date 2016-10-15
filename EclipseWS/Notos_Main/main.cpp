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
#include "AVR/ADC/ADC_Lib.h"

PrimitiveStepper test1 = PrimitiveStepper(&PORTB, 0, 2, 5000);
PrimitiveStepper test2 = PrimitiveStepper(&PORTB, 1, 2, 5000);


uint16_t isrPresc = 0;
ISR(TIMER1_COMPA_vect) {
	test1.update();
	test2.update();

	if(--isrPresc == 0) {
		ADC_Lib::start_measurement(7);
		isrPresc = 500;
	}
}

void check_voltage() {
	uint16_t voltage = ADC_Lib::lastResult;
	if(voltage > 495)
		PORTB &= ~(1<< 3);
	else
		PORTB |= (1<< 3);
}

ISR(ADC_vect) {
	ADC_Lib::update();

	if(ADC_Lib::measuredPin == 7)
		check_voltage();
}

int main() {

	DDRB |= (0b1111);
	PORTB |= (0b10000);
	DDRC |= (0b11100);

	PORTB |= 0b100;

	ADC_Lib::init(ADC_PRSC_128);

	Timer1::set_prescaler(TIMER1_PRESC_64);
	Timer1::set_mode(TIMER1_MODE_CTC);
	Timer1::set_OCR1A(50 - 1);
	sei();

	test1.setSpeed(800);
	test2.setSpeed(800);

	while(1) {
		check_voltage();

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



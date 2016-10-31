/*
 * Robot.cpp
 *
 *  Created on: 31.10.2016
 *      Author: xasin
 */

#include "Robot.h"

namespace Robot {

X2::Stepper motorA = X2::Stepper(&PORTB, 0, 2, ISR1_FREQ / ISR_CAL_FREQ, -STEPS_P_MM, STEPS_P_DEGREE);
X2::Stepper motorB = X2::Stepper(&PORTB, 1, 2, ISR1_FREQ / ISR_CAL_FREQ, -STEPS_P_MM, -STEPS_P_DEGREE);

X2::Movable Motor = X2::Movable(ISR_CAL_FREQ);

LF::Sens3 LSensor = LF::Sens3(&PINA, 0);

// Diese Funtkion liest mithilfe des ADC die Batterie-Spannung aus, und vergleicht sie mit einem Prüfwert, um sicher zu stellen dass die Batterie nicht leer ist.
// Grade jetzt werden dementsprechend einfach nur die Motoren aus oder an geschaltet.
void check_voltage() {
	uint16_t voltage = ADC_Lib::lastResult;
	if(voltage > SAFE_VOLTAGE)
		PORTB &= ~(1<< 3);
	else
		PORTB |= (1<< 3);
}

uint16_t ISR1PrescA = 1;
uint16_t ISR1PrescB = 1;
void ISR1() {
	// Aufruf der Schrittmotoren, um sich zu updaten.
	motorA.update();
	motorB.update();

	// "Prescaler", d.h. dass die nachfolgenden Funktionen nicht immer, sondern in längeren Abständen aufgerufen werden.
	if(--ISR1PrescA == 0) {
		ADC_Lib::start_measurement(7);
		ISR1PrescA = 500;
	}

	if(--ISR1PrescB == 0) {
		ISR1PrescB = ISR1_FREQ / ISR_CAL_FREQ;
		Motor.update();
		LSensor.update();
	}
}
void ISRADC() {
	ADC_Lib::update();

	if(ADC_Lib::measuredPin == 7)
		check_voltage();
}

void setLED(uint8_t value) {
	PORTC &= ~(0b11100);
	PORTC |= (value & 0b111) << 2;
}

void init() {
	// Initialisierung der Hardware-Pins (ähnlich des "pinMode" des Arduino)
	DDRB |= (0b1111);
	PORTB |= (0b10000);
	DDRC |= (0b11100);

	// Initialisierung des ADC
	ADC_Lib::init(ADC_PRSC_128, ADC_REF_AREF);

	// Initialisierung des Timer1 auf CTC (Clear Timer on Compare)-Modus. D.h. ganz normaler Timer Modus.
	Timer1::set_prescaler(TIMER1_PRESC_64);
	Timer1::set_mode(TIMER1_MODE_CTC);
	// Setzen der Dauer des Timer auf 0.2ms, d.h. also dass die TIMER1_COMPA_vect ISR mit 5000kHz aufgerufen wird.
	Timer1::set_OCR1A(50 - 1);
	sei();
}

}

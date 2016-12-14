/*
 * Robot.cpp
 *
 *  Created on: 31.10.2016
 *      Author: xasin
 */

#include "Robot.h"

// Directe Hardware-Libs
#include "../AVR/TIMER/Timer1.h"					// TIMER Bibliotheken
#include "../AVR/Actuators/Steppers/X2Stepper.h"	// Schrittmotor-Bibliothek
#include "../AVR/ADC/ADC_Lib.h"						// ADC-Bibliothek

namespace Robot {

X2::Stepper motorA = X2::Stepper(&PORTB, 0, 2, ISR1_FREQ / ISR_CAL_FREQ, -STEPS_P_MM, STEPS_P_DEGREE);
X2::Stepper motorB = X2::Stepper(&PORTB, 1, 2, ISR1_FREQ / ISR_CAL_FREQ, -STEPS_P_MM, -STEPS_P_DEGREE);

X2::Movable Motor = X2::Movable(ISR_CAL_FREQ);

Communication::RGBStatus Led = Communication::RGBStatus(&PORTC, 3, 4, 2);

LF::Sens3 LSensor = LF::Sens3(&PINA, 0);

Voltage::Battery Battery = Voltage::Battery(7, 15.682, 10.8, 12.9);

uint16_t ISR1PrescA = 1;
uint16_t ISR1PrescB = 1;
void ISR1() {
	// Aufruf der Schrittmotoren, um sich zu updaten.
	motorA.update();
	motorB.update();

	// "Prescaler", d.h. dass die nachfolgenden Funktionen nicht immer, sondern in längeren Abständen aufgerufen werden.
	if(--ISR1PrescA == 0) {
		Battery.update();
		Led.update();
		ISR1PrescA = ISR1_FREQ/ ISR_LED_FREQ;
	}

	if(--ISR1PrescB == 0) {
		ISR1PrescB = ISR1_FREQ / ISR_CAL_FREQ;
		Motor.update();
		LSensor.update();
	}
}
void ISRADC() {
	ADC_Lib::update();
	Battery.ADC_update();
}

void setMotors(bool state) {
	if(state)
		PORTB &= ~(1<< PB3);
	else
		PORTB |= (1<< PB3);
}

bool getButton() {
	return (PINB & (1<< PIN_BUTTON)) == 0;
}

InitStatus init() {
	// Initialisierung der Hardware-Pins (ähnlich des "pinMode" des Arduino)
	DDRB |= (0b1111);
	PORTB |= (0b11000);
	DDRC |= (0b11100);

	// Initialisierung des ADC
	ADC_Lib::init(ADC_PRSC_128, ADC_REF_AREF);

	// Initialisierung des Timer1 auf CTC (Clear Timer on Compare)-Modus. D.h. ganz normaler Timer Modus.
	Timer1::set_prescaler(TIMER1_PRESC_64);
	Timer1::set_mode(TIMER1_MODE_CTC);
	// Setzen der Dauer des Timer auf 0.2ms, d.h. also dass die TIMER1_COMPA_vect ISR mit 5000kHz aufgerufen wird.
	Timer1::set_OCR1A(50 - 1);
	sei();

	// Startup-Button erkennen
	if(getButton())
		return InitStatus::powerupButton;

	_delay_ms(100);


	if(Battery.getVoltage() > 2) {
		Led.setModes(0b100100100100, 0b010010010010, 0b001001001001);
		for(uint8_t i = 20; i != 0; i--) {
			if(getButton()) {
				return InitStatus::startButton;
			}
			_delay_ms(450);
		}
	}
	else
		return InitStatus::noVoltage;

	return InitStatus::noButton;
}

}

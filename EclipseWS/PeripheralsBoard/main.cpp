/*
 * main.cpp
 *
 *  Created on: 30.03.2017
 *      Author: xasin
 */

#include "AVR/ADC/ADC_Lib.h"
#include "AVR/TIMER/Timer1.h"
#include "AVR/TIMER/Timer0.h"

#include "AVR/Communication/NEW_TWI/TWI.h"

#include "Localcode/BallLaser.h"
#include "Localcode/ServoControl.h"

#include <avr/interrupt.h>

#include <util/delay.h>

BallLaser ballLaser(0, 0, &PORTB);
ServoControl servos = ServoControl();

ISR(TWI_vect) {
	TWI::updateTWI();
}

uint8_t timer0_presc_A = 0;
ISR(TIMER0_COMPA_vect) {
	switch(timer0_presc_A++) {
	default: break;

	case 0:
	ballLaser.update();
	servos.update();
	break;

	case 1:
	if(ballLaser.nextLaserOff())
		ballLaser.update();
	break;

	case 4:
	timer0_presc_A = 0;
	break;
	}
}

ISR(ADC_vect) {
	ADC_Lib::update();
	ballLaser.ADCUpdate();
}

int main() {
	DDRB |= (1<< PB0 | 1<< PB1 | 1<< PB2);
	DDRD |= (0b11 << PD6);

	Timer0::set_mode(TIMER0_MODE_CTC);
	Timer0::set_OCR0A(250 -1);					// With 256 prescaler, exactly 250Hz
	Timer0::set_prescaler(TIMER0_PRESC_256);

	TWI::init();
	TWI::setAddr(0x10);

	ADC_Lib::init(ADC_PRSC_128, ADC_REF_AREF);

	sei();

	_delay_ms(2000);
	servos.targetMode = RETRACTED;

	while(1) {
	}
}

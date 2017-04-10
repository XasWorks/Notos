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

#include <avr/interrupt.h>

#include <util/delay.h>

BallLaser ballLaser(0, 0, &PORTB);

ISR(TWI_vect) {
	TWI::updateTWI();
}

uint8_t sftPresc = 0;
ISR(TIMER0_COMPA_vect) {
	ballLaser.update();
}

ISR(ADC_vect) {
	ADC_Lib::update();
	ballLaser.ADCUpdate();
}

void waitFor(uint16_t ms) {
	while(ms-- != 0)
		_delay_ms(1);
}

void setServo(float pos) {
	if(pos < 0)
		pos = 0;
	if(pos > 180)
		pos = 180;
	OCR1A = 1500 + 3500 * (pos/180);
}

int main() {
	DDRB |= (1<< PB0 | 1<< PB1);
	DDRD |= (0b11 << PD6);

	Timer1::set_mode(TIMER1_MODE_FPWM);
	ICR1 = 40000 -1;
	Timer1::set_prescaler(TIMER1_PRESC_8);

	Timer0::set_mode(TIMER0_MODE_CTC);
	Timer0::set_OCR0A(156 -1);					// With 1024 prescaler, roughly 100Hz
	Timer0::set_prescaler(TIMER0_PRESC_1024);

	TWI::init();
	TWI::setAddr(0x10);

	ADC_Lib::init(ADC_PRSC_128, ADC_REF_AREF);

	setServo(90);
	_delay_ms(1000);

	sei();



	while(1) {
		if(ballLaser.hitData.hitStatus < 0)
			PORTD |= (1<< 6);
		else
			PORTD &= ~(1<< 6);
	}
}



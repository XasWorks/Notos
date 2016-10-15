/*
 * main.c
 *
 *  Created on: Oct 9, 2016
 *      Author: xasin
 */

#include <avr/io.h>
#include <util/delay.h>

int main() {

	DDRB |= (0b1111);
	PORTB |= (0b10000);
	DDRC |= (0b11100);

	uint8_t i = 0;
	while(1) {
		if((PINB & (1<<4)) == 0) {
			PORTB |= 1;
		}
		else {
			PORTB &= ~(1);
		}
	}

	while(1) {}
	return 1;
}



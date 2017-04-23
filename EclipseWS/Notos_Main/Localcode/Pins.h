/*
 * Pins.h
 *
 *  Created on: Dec 14, 2016
 *      Author: xasin
 */

#ifndef LOCALCODE_PINS_H_
#define LOCALCODE_PINS_H_

#define PIN_ALF_SENSORS		0
#define PINx_ELF_SENSORS	PIND
#define	PIN_ELF_SENSORS		0

#define PIN_BATTERY 	7

#define PORTx_BUTTON	PORTB
#define PINx_BUTTON 	PINB
#define PIN_BUTTON 		4

#define PORTx_RGB 	PORTC
#define PIN_RGB_R		3
#define PIN_RGB_G		4
#define PIN_RGB_B		2

#define PORTx_STEPPERS 	PORTB
#define DDRx_STEPPERS	DDRB
#define PIN_STEPPER0_S	0
#define PIN_STEPPER0_D	2
#define PIN_STEPPER1_S	1
#define PIN_STEPPER1_D	2
#define PIN_STEPPER_E	3

#define PORTx_DINPUTS	PORTD
#define PINx_DINPUTS	PIND

#define PIN_BUMPER 		2
#define PIN_CONDUCTOR	4
#define PIN_BALLBOOP	3


#define PINx_TILT_SENSOR 3
#define PINx_GREEN_SENSOR	2

#endif /* LOCALCODE_PINS_H_ */

/*
 * Pins.h
 *
 *  Created on: Dec 14, 2016
 *      Author: xasin
 */

#ifndef LOCALCODE_PINS_H_
#define LOCALCODE_PINS_H_

#define PIN_LF_SENSOR_START 	0
#define PORTx_LF_SENSOR			PORTA

#define PIN_BATTERY 	7

#define PORTx_BUTTON	PORTB
#define PINx_BUTTON 	PINB
#define PIN_BUTTON 	4

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

#define PINx_BUMPER 	PINA
#define PORTx_BUMPER PORTA
#define PIN_BUMPER 	4

#define PINx_TILT_SENSOR 5

#endif /* LOCALCODE_PINS_H_ */

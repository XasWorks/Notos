/*
 * Robot.h
 *
 *  Created on: 31.10.2016
 *      Author: xasin
 */

#ifndef LOCALCODE_ROBOT_H_
#define LOCALCODE_ROBOT_H_

#include <avr/io.h>
#include <avr/interrupt.h>

// Utility-Libs (für Motorsteuerung etc.)
#include "../AVR/Movement/X2/X2-Movable.h"			// Motor-Steuerung
#include "../AVR/Sensors/LineFollow/LF3Sens.h"		// LineFollow Bibliotheken


// -- Basische defines für System-Werte
#define ISR1_FREQ 	5000 	// Frequenz des TIMER1-ISR
#define ISR_CAL_FREQ	50		// Frequenz der Movable-Kalkulationen
#define SAFE_VOLTAGE 495	// Minimum für die Spannungs-Messung (in ADC-Wert)

// Definitionen des Bewegungs-Systemes
#define MICROSTEPPING 8		// Microstepping-Definition
#define MOTOR_WHEEL_DIAMETER 30
#define MOTOR_WHEEL_OUTWARDS_SHIFT (35 + 2.5 + 2 + 10)
// #define STEPS_P_MM ((200 * MICROSTEPPING) / (M_PI * MOTOR_WHEEL_DIAMETER))
#define STEPS_P_MM 	2.1221 * MICROSTEPPING
//#define STEPS_P_DEGREE (((2 * M_PI * MOTOR_WHEEL_OUTWARDS_SHIFT) / 360) * STEPS_P_MM)
#define STEPS_P_DEGREE 	1.8334 * MICROSTEPPING

// Der Robot-Namespace, ein Haupt-Namespace für alle wichtigen Basisfunktionen des Roboters
namespace Robot {

extern X2::Movable	Motor;
extern LF::Sens3 	LSensor;

void ISR1();
void ISRADC();

void setLED(uint8_t value);

void init();

}



#endif /* LOCALCODE_ROBOT_H_ */

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
#include "../AVR/Sensors/LineFollow/LFA2Sens.h"		// LineFollow Bibliotheken
#include "../AVR/Communication/RGBStatus/RGBStatus.h"	// LED-Lib
#include "../AVR/Sensors/Voltage/Battery.h"			// Batterie-Überprüfung
#include "../AVR/Communication/NEW_TWI/TWI.h"

#include "Pins.h"
#include "TiltSensor.h"

#include "PeripheralsComs/LaserFinder.h"

// -- Basische defines für System-Werte
#define ISR1_FREQ 	5000 	// Frequenz des TIMER1-ISR
#define ISR_CAL_FREQ	100	// Frequenz der Movable-Kalkulationen
#define ISR_LED_FREQ	6	// Frequenz der LED und Battery-Checking
#define SAFE_VOLTAGE 10.5	// Minimum für die Spannungs-Messung (in ADC-Wert)

// Definitionen des Bewegungs-Systemes
#define MICROSTEPPING 4		// Microstepping-Definition
#define MOTOR_WHEEL_DIAMETER 30
#define MOTOR_WHEEL_OUTWARDS_SHIFT (35 + 2.5 + 2 + 10)
// #define STEPS_P_MM ((200 * MICROSTEPPING) / (M_PI * MOTOR_WHEEL_DIAMETER))
#define STEPS_P_MM 	-2.1221 * MICROSTEPPING
//#define STEPS_P_DEGREE (((2 * M_PI * MOTOR_WHEEL_OUTWARDS_SHIFT) / 360) * STEPS_P_MM)
#define ROTATION_CORRECT 1.4
#define STEPS_P_DEGREE 	1.8334 * MICROSTEPPING * ROTATION_CORRECT



// Der Robot-Namespace, ein Haupt-Namespace für alle wichtigen Basisfunktionen des Roboters
namespace Robot {

enum InitStatus : uint8_t { noButton, noVoltage, powerupButton, startButton, lowBattery};

extern X2::Movable	Motor;
extern LF::ASens2	LSensor;
extern Communication::RGBStatus Led;
extern Voltage::Battery Battery;
extern Peripheral::LaserFinder Laser;

void ISR1();
void ISRADC();

void waitForSensors();

void setMotors(bool state);

InitStatus init();

bool getBumper();
bool getButton();

}



#endif /* LOCALCODE_ROBOT_H_ */

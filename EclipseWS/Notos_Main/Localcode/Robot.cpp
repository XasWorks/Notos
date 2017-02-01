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

using namespace Sensor;

X2::Stepper motorA = X2::Stepper(&PORTB, 0, 2, ISR1_FREQ / ISR_CAL_FREQ, -STEPS_P_MM, STEPS_P_DEGREE);
X2::Stepper motorB = X2::Stepper(&PORTB, 1, 2, ISR1_FREQ / ISR_CAL_FREQ, -STEPS_P_MM, -STEPS_P_DEGREE);

X2::Movable Motor = X2::Movable(ISR_CAL_FREQ);

Communication::RGBStatus Led = Communication::RGBStatus(&PORTC, 3, 4, 2);

LF::Sens3 LSensor = LF::Sens3(&PINA, 0);

Voltage::Battery Battery = Voltage::Battery(7, 15.682, SAFE_VOLTAGE, 12.9);

uint16_t ISR1PrescA = 1;
uint16_t ISR1PrescB = 1;
volatile uint8_t sensorStatus;
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
		ISR1PrescB = ISR1_FREQ / ISR_CAL_FREQ /2;
		if(sensorStatus != 0) {
			Motor.update();
			sensorStatus = 0;
		}
		else {
			LSensor.update();
			Accelleration::initMeasurement();
			sensorStatus = 1;
		}
	}
}
void ISRADC() {
	ADC_Lib::update();
	Battery.ADC_update();
	Accelleration::analogUpdate();
}

void waitForSensors() {
	while(sensorStatus != 1) {}
	sensorStatus = 2;
}

void setMotors(bool state) {
	if(state)
		PORTB &= ~(1<< PB3);
	else
		PORTB |= (1<< PB3);
}

#ifdef PIN_BUMPER
bool getBumper() {
	return (PINx_BUMPER & (1<< PIN_BUMPER)) == 0;
}
#endif
bool getButton() {
	return (PINx_BUTTON & (1<< PIN_BUTTON)) == 0;
}

InitStatus init() {
	// Initialisierung der Hardware-Pins (ähnlich des "pinMode" des Arduino)
	DDRB |= (0b1111);
	PORTB |= (0b11000);
	DDRC |= (0b11100);

#ifdef PIN_BUMPER
	PORTx_BUMPER |= (1<< PIN_BUMPER);
#endif

	// Initialisierung des ADC
	ADC_Lib::init(ADC_PRSC_128, ADC_REF_AREF);

	// Initialisierung des Timer1 auf CTC (Clear Timer on Compare)-Modus. D.h. ganz normaler Timer Modus.
	Timer1::enable_CTC(ISR1_FREQ);

	// Startup-Button erkennen
	if(getButton())
		return InitStatus::powerupButton;

	_delay_ms(100);


	if(Battery.getVoltage() > SAFE_VOLTAGE) {
		Led.setModes(0b100100100100, 0b010010010010, 0b001001001001);
		for(uint8_t i = 6; i != 0; i--) {
			_delay_ms(450);
			if(getButton()) {
				return InitStatus::startButton;
			}
		}

		return InitStatus::noButton;
	}
	else if(Battery.getVoltage() > 2)
		return InitStatus::lowBattery;
	else
		return InitStatus::noVoltage;
}

}

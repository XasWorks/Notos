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

X2::Stepper motorA = X2::Stepper(&PORTx_STEPPERS, PIN_STEPPER0_S, PIN_STEPPER0_D, ISR1_FREQ / ISR_CAL_FREQ, -STEPS_P_MM, STEPS_P_DEGREE);
X2::Stepper motorB = X2::Stepper(&PORTx_STEPPERS, PIN_STEPPER1_S, PIN_STEPPER1_D, ISR1_FREQ / ISR_CAL_FREQ, -STEPS_P_MM, -STEPS_P_DEGREE);

X2::Movable Motor = X2::Movable(ISR_CAL_FREQ);

Communication::RGBStatus Led = Communication::RGBStatus(&PORTx_RGB, PIN_RGB_R, PIN_RGB_G, PIN_RGB_B);

LF::ASens2 LSensor = LF::ASens2(PIN_ALF_SENSORS, &PINx_ELF_SENSORS, PIN_ELF_SENSORS);

Voltage::Battery Battery = Voltage::Battery(PIN_BATTERY, 15.682, SAFE_VOLTAGE, 12.9);

Peripheral::LaserFinder Laser = Peripheral::LaserFinder();

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
			Tilting::initMeasurement();
			LSensor.update();
			sensorStatus = 1;
		}
	}
}
void ISRADC() {
	ADC_Lib::update();
	Battery.ADC_update();
	Tilting::analogUpdate();
	LSensor.ADCUpdate();
}

void waitForSensors() {
	while(sensorStatus != 1 || !LSensor.isUpdated()) {
		_delay_ms(1);
	}
	sensorStatus = 2;
}

void setMotors(bool state) {
	if(state)
		PORTx_STEPPERS &= ~(1<< PIN_STEPPER_E);
	else
		PORTx_STEPPERS |= (1<< PIN_STEPPER_E);
}


bool getBumper() {
	return (PINx_DINPUTS & (1<< PIN_BUMPER)) == 0;
}
bool getButton() {
	return (PINx_BUTTON & (1<< PIN_BUTTON)) == 0;
}
bool getGroundConductive() {
	return (PINx_DINPUTS & (1<< PIN_CONDUCTOR)) == 0;
}
bool getBallBoop() {
	return (PINx_DINPUTS & (1<< PIN_BALLBOOP)) == 0;
}


InitStatus init() {
	// Initialisierung der Hardware-Pins (ähnlich des "pinMode" des Arduino)

	PORTx_BUTTON |= (1<< PIN_BUTTON);
	PORTx_STEPPERS |= (1<< PIN_STEPPER_E);
	DDRx_STEPPERS |= (1<< PIN_STEPPER_E);

	PORTx_DINPUTS |= (1<< PIN_BUMPER | 1<< PIN_BALLBOOP | 1<< PIN_CONDUCTOR);

	// Initialisierung des ADC
	ADC_Lib::init(ADC_PRSC_128, ADC_REF_AREF);

	TWI::init();

	// Initialisierung des Timer1 auf CTC (Clear Timer on Compare)-Modus. D.h. ganz normaler Timer Modus.
	Timer1::enable_CTC(ISR1_FREQ);

	// Startup-Button erkennen
	if(getButton())
		return InitStatus::powerupButton;

	_delay_ms(100);


	if(Battery.getVoltage() > SAFE_VOLTAGE) {
		Led.setModes(0b100100100100, 0b010010010010, 0b001001001001);
		for(uint8_t i = 10; i != 0; i--) {
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

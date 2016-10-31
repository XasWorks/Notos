/*
 * main.c
 *
 *  Created on: Oct 9, 2016
 *      Author: xasin
 */


// Die folgenden Bibliotheken sind Standard-Header-Dateien, um den Microcontroller nutzen zu können.
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>

// Die "Timer" Bilbiothek erlaubt eine vereinfachte Nutzung der eingebauten Timer des Mega32
#include "AVR/TIMER/Timer1.h"
#include "AVR/Actuators/Steppers/X2Stepper.h"
// Die ADC-Bibliothek erlaubt einfachen Zugriff auf den Analog-Digital-Wandler, vergleichbar mit der Arduino "AnalogRead" Funktion
#include "AVR/ADC/ADC_Lib.h"

#include "AVR/Movement/X2/X2-Movable.h"

#include "AVR/Sensors/LineFollow/LF3Sens.h"

#define ISR_1_FREQ 5000
#define ISR_CAL_FREQ 50

#define MICROSTEPPING 8
#define MOTOR_WHEEL_DIAMETER 30
#define MOTOR_WHEEL_OUTWARDS_SHIFT (35 + 2.5 + 2 + 10)
#define STEPS_P_MM ((200 * MICROSTEPPING) / (M_PI * MOTOR_WHEEL_DIAMETER))
#define STEPS_P_DEGREE (((2 * M_PI * MOTOR_WHEEL_OUTWARDS_SHIFT) / 360) * STEPS_P_MM)

// Instanzierung der zwei Test-Schrittmotoren
X2::Stepper test1 = X2::Stepper(&PORTB, 0, 2, ISR_1_FREQ / ISR_CAL_FREQ, -STEPS_P_MM, STEPS_P_DEGREE);
X2::Stepper test2 = X2::Stepper(&PORTB, 1, 2, ISR_1_FREQ / ISR_CAL_FREQ, -STEPS_P_MM, -STEPS_P_DEGREE);

X2::Movable testMotor = X2::Movable(ISR_CAL_FREQ);

LF::Sens3 testSensor = LF::Sens3(&PINA, 0);

// Diese Funtkion liest mithilfe des ADC die Batterie-Spannung aus, und vergleicht sie mit einem Prüfwert, um sicher zu stellen dass die Batterie nicht leer ist.
// Grade jetzt werden dementsprechend einfach nur die Motoren aus oder an geschaltet.
void check_voltage() {
	uint16_t voltage = ADC_Lib::lastResult;
	if(voltage > 495)
		PORTB &= ~(1<< 3);
	else
		PORTB |= (1<< 3);
}


uint16_t isrPrescA = 1;
uint16_t isrPrescB = 1;

// Eine "ISR"-Funktion ist eine Funktion, welche zu bestimmten Zeitpunkten automatisch aufgerufen wird.
// In dieserm Fall handelt es sich um die "TIMER1 - CompareInterrupt A" ISR. D.h. der Timer, hier aufgerufen alle 0.2ms
ISR(TIMER1_COMPA_vect) {

	// Aufruf der Schrittmotoren, um sich zu updaten.
	test1.update();
	test2.update();

	// "Prescaler", d.h. dass die nachfolgenden Funktionen nicht immer, sondern in längeren Abständen aufgerufen werden.
	if(--isrPrescA == 0) {
		ADC_Lib::start_measurement(7);
		isrPrescA = 500;
	}

	if(--isrPrescB == 0) {
		isrPrescB = ISR_1_FREQ / ISR_CAL_FREQ;
		testMotor.update();
		testSensor.update();
	}
}

// Diese ISR wird aufgerufen, wenn der ADC mit einer Umwandlung fertig ist. An sich ist es nur eine Hardware-Sache, also muss es nicht direkt verstanden werden.
ISR(ADC_vect) {
	ADC_Lib::update();

	if(ADC_Lib::measuredPin == 7)
		check_voltage();
}

void setLED(uint8_t value){
	PORTC &= ~(0b11100);
	PORTC |= (value & 0b111) << 2;
}


// Die main-Methode des Roboters. Hier steht alles /wirklich/ wichtige drinnen, nämlich der eigentliche Programmcode.
int main() {

	// Initialisierung der Hardware-Pins (ähnlich des "pinMode" des Arduino)
	DDRB |= (0b1111);
	PORTB |= (0b10000);
	DDRC |= (0b11100);

	PORTB |= 0b100;

	// Initialisierung des ADC
	ADC_Lib::init(ADC_PRSC_128, ADC_REF_AREF);


	// Initialisierung des Timer1 auf CTC (Clear Timer on Compare)-Modus. D.h. ganz normaler Timer Modus.
	Timer1::set_prescaler(TIMER1_PRESC_64);
	Timer1::set_mode(TIMER1_MODE_CTC);
	// Setzen der Dauer des Timer auf 0.2ms, d.h. also dass die TIMER1_COMPA_vect ISR mit 5000kHz aufgerufen wird.
	Timer1::set_OCR1A(50 - 1);
	sei();

	testMotor.setSpeed(0);
	testMotor.setRotationSpeed(360);
	testMotor.continuousMode();

	// Dauerschleife mit Motor-Test-Programm.
	while(1) {
		testMotor.setRotationSpeed(testSensor.lineOffset * 360.0 / 127);
		switch(testSensor.lineStatus) {
		case LF::OK:
			setLED(0b100);
		break;

		case LF::LOST:
			setLED(0b010);
		break;

		default:
			setLED(0b001);
		break;
		}
	}

	return 1;
}

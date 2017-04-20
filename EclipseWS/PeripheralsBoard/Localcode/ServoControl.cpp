/*
 * ServoControl.cpp
 *
 *  Created on: 19.04.2017
 *      Author: xasin
 */

#include "ServoControl.h"

ServoControl::ServoControl() {
	Timer1::set_mode(TIMER1_MODE_FPWM);
	ICR1 = 40000 -1;
	Timer1::set_prescaler(TIMER1_PRESC_8);

	this->setArmsTo(RETRACTED);
}

bool ServoControl::slavePrepare() {
	if(TWI::targetReg != PeripheralCommand::SET_ARM_MODE)
		return false;

	TWI::dataPacket = (uint8_t *)&targetMode;
	TWI::dataLength = 1;

	return true;
}

void ServoControl::setServoA(float percentage) {
	OCR1A = 1650 + 3100 * (percentage/100);
}
void ServoControl::setServoB(float percentage) {
	OCR1B = 1750 + 3112 * (percentage/100);
}

void ServoControl::setArmsTo(GrabbingArmModes mode) {
	moveDelay = 70;
	this->currentMode = mode;

	this->setServoA(servoAPositions[(uint8_t)mode]);
	this->setServoB(servoBPositions[(uint8_t)mode]);
}

void ServoControl::update() {
	if(moveDelay != 0)
		moveDelay--;
	else if(targetMode != currentMode) {
		if(currentMode == RETRACTED)
			this->setArmsTo(RAISED_OPEN);
		else if((currentMode == LOWERED_OPEN) && (targetMode == RAISED_CLOSED))
			this->setArmsTo(LOWERED_CLOSED);
		else
			this->setArmsTo(targetMode);
	}
}

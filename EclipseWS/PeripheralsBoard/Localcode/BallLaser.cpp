/*
 * BallLaser.cpp
 *
 *  Created on: 31.03.2017
 *      Author: xasin
 */

#include "BallLaser.h"

BallLaser::BallLaser(uint8_t const greyscalePin, uint8_t const laserPin, uint8_t volatile * const laserPort)
	: greyscalePin(greyscalePin), lzrPin(laserPin), lzrPort(laserPort) {

	*(lzrPort -1) |= (1<< lzrPin);
}

void BallLaser::ADCUpdate() {
	if(ADC_Lib::measuredPin != greyscalePin)
		return;

	switch(phase) {
	case S_BACKGROUND:
	case C_BACKGROUND:
		if((ADC_Lib::lastResult > 900) || (adjustValue == 0)) {
			oPhase = phase;

			phase = PULLDOWN_ADJUST;
			adjustValue = 1;
			this->setPulldown(1);
		}
		else {
			this->background = ADC_Lib::lastResult;
			phase = (LaserPhase)(phase + 1);
			*lzrPort |= (1<< lzrPin);
		}
	break;

	case S_LASER:
		phase = (LaserPhase)(phase - 1);
	case C_LASER:
		phase = (LaserPhase)(phase - 1);

		this->reflected = ADC_Lib::lastResult;
		this->reflectance = this->reflected - this->background;

		*lzrPort &= ~(1<< lzrPin);
	break;

	case PULLDOWN_ADJUST:
		if(ADC_Lib::lastResult < 900) {
			adjustValue = 255;
			phase = oPhase;
		}
		else {
			setPulldown(++adjustValue);

			if(adjustValue == 7) {
				adjustValue = 255;
				phase = oPhase;
			}
		}
	break;

	default: break;
	}
}

void BallLaser::update() {
	if(phase != PULLDOWN_ADJUST)
		if(adjustValue != 0)
			adjustValue--;

	if(phase != PAUSED)
		ADC_Lib::start_measurement(greyscalePin);
}

void BallLaser::setPulldown(uint8_t value) {
	DDRB &= ~(0b111 << PB3);
	DDRB |= ((value & 0b111) << PB3);
}
uint8_t BallLaser::getPulldown() {
	return (DDRB & (0b111 << PB3)) >> PB3;
}


uint8_t BallLaser::getReflectance() {
	if(reflectance < 0)
		return 0;
	if(reflectance > 255)
		return 255;

	return reflectance;
}

void BallLaser::laserOff() {
	phase = PAUSED;
	*lzrPort &= ~(1<< lzrPin);
}

bool BallLaser::slavePrepare() {
	if(TWI::targetReg == LZR_CMD_START) {
		TWI::dataLength = 6;
		TWI::dataPacket = (uint8_t *)&this->background;

		return true;
	}

	else if(TWI::targetReg == LZR_CMD_START+1) {
		this->laserOff();
		return true;
	}
	else if(TWI::targetReg == LZR_CMD_START+2) {
		phase = C_BACKGROUND;
		return true;
	}
	else if(TWI::targetReg == LZR_CMD_START+3) {
		phase = S_BACKGROUND;
		ADC_Lib::start_measurement(greyscalePin);

		return true;
	}

	return false;
}

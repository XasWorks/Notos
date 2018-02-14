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
	case PULLDOWN_ADJUSTMENT:
		if(ADC_Lib::lastResult < 900) {
			adjustValue = 255;
			phase = LASER_MEASURING;
		}
		else {
			setPulldown(++adjustValue);

			if(adjustValue == 7) {
				adjustValue = 255;
				phase = LASER_MEASURING;
			}
		}
	break;

	case LASER_MEASURING:
		if((laserTimeout & 0b1) == 0) {
			this->background = ADC_Lib::lastResult;
			*(lzrPort) |= (1<< lzrPin);
		}
		else {
			this->reflectance = ADC_Lib::lastResult - this->background;
			*(lzrPort) &= ~(1<< lzrPin);

			if(this->reflectance >= this->detectThreshold) {
				if(hitData.hitStatus < 0)
					hitData.hitStatus = BALL_ALLOWED_MISSES;
				else {
					hitData.hitStatus++;
					if(hitData.hitStatus == BALL_CONSEC_HITS)
						hitData.hitStatus = BALL_ALLOWED_MISSES;
				}
			}
			else {
				if(hitData.hitStatus < 0)
					hitData.hitStatus++;
				else if(hitData.hitStatus != 0)
					hitData.hitStatus--;
			}
		}

		laserTimeout--;
	break;

	default: break;
	}
}

void BallLaser::update() {
	if(phase == LASER_MEASURING) {
		if(adjustValue != 0)
			adjustValue--;

		if(((laserTimeout & 0b1) == 0) && (adjustValue == 0)) {
			phase = PULLDOWN_ADJUSTMENT;
			adjustValue = 1;
			setPulldown(1);
		}
		else if(laserTimeout != 0)
			ADC_Lib::start_measurement(greyscalePin);
	}
	else
		ADC_Lib::start_measurement(greyscalePin);
}

bool BallLaser::nextLaserOff() {
	return (laserTimeout & 0b1);
}

void BallLaser::setPulldown(uint8_t value) {
	DDRB &= ~(0b111 << PB3);
	DDRB |= ((value & 0b111) << PB3);
}

void BallLaser::laserOff() {
	laserTimeout = 0;
	*lzrPort &= ~(1<< lzrPin);
}

bool BallLaser::slavePrepare() {
	switch((PeripheralCommand)TWI::targetReg) {

	case PeripheralCommand::READ_LASER:
		TWI::dataLength = 2;

		if(this->reflectance < 0)
			hitData.reflectance = 0;
		else if(this->reflectance > 0xff)
			hitData.reflectance = 0xff;
		else
			hitData.reflectance = this->reflectance;

		if(laserTimeout == 0)
			this->hitData.hitStatus = 0;
		this->laserTimeout |= 0b11111110;

		TWI::dataPacket = (uint8_t *)&this->hitData;

		return true;

	case PeripheralCommand::SET_THRESHOLD:
		TWI::dataLength = 1;
		TWI::dataPacket= (uint8_t *)&this->detectThreshold;

		return true;


	default:
		return false;
	}
}

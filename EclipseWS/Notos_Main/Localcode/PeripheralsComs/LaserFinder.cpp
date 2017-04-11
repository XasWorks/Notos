/*
 * LaserFinder.cpp
 *
 *  Created on: 05.04.2017
 *      Author: xasin
 */

#include "LaserFinder.h"
#include <util/delay.h>

namespace Peripheral {

LaserFinder::LaserFinder() {
}

bool LaserFinder::masterPrepare() {
	if((tasks & 0b1) != 0) {
		TWI::targetAddr = ((0x10<<1) | 0b1);

		TWI::targetReg  = PeripheralCommand::READ_LASER;
		TWI::dataPacket = (uint8_t *)&hitData;
		TWI::dataLength = 2;

		return true;
	}

	if((tasks & 0b10) != 0) {
		TWI::targetAddr = 0x10 << 1;
		
		TWI::dataLength = 1;
		TWI::dataPacket = (uint8_t *)&threshold;
		TWI::targetReg = PeripheralCommand::SET_THRESHOLD;

		return true;
	}

	return false;
}

bool LaserFinder::masterEnd() {
	isPresent = true;

	switch((PeripheralCommand)TWI::targetReg) {
	case READ_LASER:
		tasks &= ~(0b1);
	break;

	case SET_THRESHOLD:
	 	tasks &= ~(0b10);
	break;
	default: break;
	}

	return false;
}

void LaserFinder::error() {
	this->errorCode = TWI::readSR();

	isPresent = false;
	tasks = 0;
}

void LaserFinder::ping() {
	tasks |= 0b1;
	TWI::checkMasterJobs();
}

void LaserFinder::pingAndWait() {
	this->ping();
	while(tasks & 0b1) {
		_delay_ms(1);
	}
}

void LaserFinder::setThreshold(uint8_t newThreshold) {
	this->threshold = newThreshold;
	tasks |= (0b10);
	TWI::checkMasterJobs();
}

} /* namespace Peripheral */

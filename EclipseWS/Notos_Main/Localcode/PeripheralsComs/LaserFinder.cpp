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
	if(tasks == 0)
		return false;

	TWI::targetAddr = ((0x10<<1) | 0b1);

	if((tasks & 0b1) != 0) {
		TWI::targetReg  = PeripheralCommand::READ_LASER;
		TWI::dataPacket = (uint8_t *)&hitData;
		TWI::dataLength = 2;
	}

	return true;
}

bool LaserFinder::masterEnd() {
	isPresent = true;

	switch((PeripheralCommand)TWI::targetReg) {
	case READ_LASER:
		tasks &= ~(0b1);
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

} /* namespace Peripheral */

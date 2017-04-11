/*
 * LaserFinder.h
 *
 *  Created on: 05.04.2017
 *      Author: xasin
 */

#ifndef LOCALCODE_PERIPHERALSCOMS_LASERFINDER_H_
#define LOCALCODE_PERIPHERALSCOMS_LASERFINDER_H_

#include "../../AVR/Communication/NEW_TWI/Job.h"
#include "../Packets.h"


namespace Peripheral {

class LaserFinder: public TWI::Job {
private:
	volatile uint8_t tasks = 0;
	uint8_t threshold = 20;

public:
	volatile bool isPresent = false;
	volatile TWI::Status errorCode;

	LaserReadData hitData;

	LaserFinder();

	bool masterPrepare();
	bool masterEnd();

	void error();

	void ping();
	void pingAndWait();

	void setThreshold(uint8_t newThreshold);
};

} /* namespace Peripheral */

#endif /* LOCALCODE_PERIPHERALSCOMS_LASERFINDER_H_ */

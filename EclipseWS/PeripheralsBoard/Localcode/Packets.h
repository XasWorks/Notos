/*
 * Packets.h
 *
 *  Created on: 05.04.2017
 *      Author: xasin
 */

#ifndef PACKETS_H_
#define PACKETS_H_

enum PeripheralCommand : uint8_t {
	READ_LASER,
	SET_THRESHOLD,
};

struct LaserReadData {
	volatile uint8_t reflectance = 0;
	volatile int8_t hitStatus 	 = 0;
};

#endif /* PACKETS_H_ */

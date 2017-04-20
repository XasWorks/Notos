/*
 * BallLaser.h
 *
 *  Created on: 31.03.2017
 *      Author: xasin
 */

#ifndef BALLLASER_H_
#define BALLLASER_H_

#include "../AVR/Communication/NEW_TWI/Job.h"
#include "../AVR/Communication/NEW_TWI/TWI.h"
#include "../AVR/ADC/ADC_Lib.h"

#include "Packets.h"

#define BALL_CONSEC_HITS			1
#define BALL_ALLOWED_MISSES		-10

enum LaserPhase : uint8_t {
	PULLDOWN_ADJUSTMENT,
	LASER_MEASURING,
};

class BallLaser : TWI::Job {
private:
	const uint8_t greyscalePin;
	const uint8_t lzrPin;
	uint8_t volatile * const lzrPort;

	volatile uint16_t 	background 	= 0;
	volatile uint16_t 	reflected 	= 0;
	volatile int16_t 	reflectance = 0;

	volatile uint8_t 	detectThreshold = 20;

	volatile LaserPhase phase = PULLDOWN_ADJUSTMENT;

	uint8_t laserTimeout = 0;
	uint8_t adjustValue = 0;

	void setPulldown(uint8_t value);

public:
	LaserReadData hitData;

	BallLaser(uint8_t const greyscalePin, uint8_t const laserPin, uint8_t volatile * const laserPort);

	void ADCUpdate();
	void update();

	void laserOff();

	bool slavePrepare();
};

#endif /* BALLLASER_H_ */

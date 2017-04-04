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

#define LZR_CMD_START 0

enum LaserPhase : uint8_t {
	PAUSED			= 0xf0,

	C_BACKGROUND	= 0b10,
	C_LASER			= 0b11,

	S_BACKGROUND	= 0b00,
	S_LASER			= 0b01,

	PULLDOWN_ADJUST	= 0b100,
};

class BallLaser : TWI::Job {
private:
	const uint8_t greyscalePin;
	const uint8_t lzrPin;
	uint8_t volatile * const lzrPort;

	volatile uint16_t 	background 	= 0;
	volatile uint16_t 	reflected 	= 0;
	volatile int16_t 	reflectance = 0;

	volatile LaserPhase phase = PULLDOWN_ADJUST;
	volatile LaserPhase oPhase = C_BACKGROUND;

	uint8_t adjustValue = 0;

	void setPulldown(uint8_t value);
	uint8_t getPulldown();

public:
	BallLaser(uint8_t const greyscalePin, uint8_t const laserPin, uint8_t volatile * const laserPort);

	void ADCUpdate();
	void update();

	uint8_t getReflectance();

	void laserOff();

	bool slavePrepare();
};

#endif /* BALLLASER_H_ */

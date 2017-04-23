/*
 * ServoControl.h
 *
 *  Created on: 19.04.2017
 *      Author: xasin
 */

#ifndef SERVOCONTROL_H_
#define SERVOCONTROL_H_

#include "../AVR/Communication/NEW_TWI/Job.h"
#include "../AVR/Communication/NEW_TWI/TWI.h"

#include "../AVR/TIMER/Timer1.h"

#include "Packets.h"

class ServoControl: public TWI::Job {
private:
	uint8_t moveDelay = 0;

	GrabbingArmModes currentMode = RETRACTED;

	const uint8_t servoAPositions[5] = {100, 50, 0, 50, 0};
	const uint8_t servoBPositions[5] = {100, 45, 45, 80, 100};

	void setServoA(float percentage);
	void setServoB(float percentage);

	void setArmsTo(GrabbingArmModes);

public:
	GrabbingArmModes targetMode = RAISED_CLOSED;

	ServoControl();

	bool slavePrepare();

	void update();
};

#endif /* SERVOCONTROL_H_ */

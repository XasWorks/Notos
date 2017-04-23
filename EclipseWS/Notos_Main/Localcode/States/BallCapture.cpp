/*
 * BallCapture.cpp
 *
 *  Created on: 20.04.2017
 *      Author: xasin
 */

#include "BallCapture.h"

namespace State {
namespace Ball {

using namespace Robot;
using Communication::Pattern;

bool snatchBall() {
	Motor.cancel();
	Laser.setArmMode(RAISED_OPEN);

	Motor.movedDistance = 0;
	Motor.setSpeeds(50, 0);
	Motor.moveBy(400);
	bool hasBall = false;
	while(1) {
		if(getBallBoop()) {
			hasBall = true;
			break;
		}
		if(Motor.isReady())
			break;
	}
	Motor.cancel();
	Motor.setSpeeds(150, 60);

	if(!hasBall) {
		Motor.moveF(-Motor.movedDistance);

		return false;
	}
	else {
		Motor.moveF(-10);
		Motor.rotateF(-35);
		Laser.setArmMode(RAISED_CLOSED);
		_delay_ms(500);
		Motor.rotateF(35);
		Motor.moveF(-Motor.movedDistance);

		return true;
	}
}

void positionInCenter(float assumedX, float assumedY) {
	Motor.rotateF(atan2(-assumedX, -assumedY) / M_PI * 180 - Motor.movedRotation);
	Motor.moveF(hypot(assumedX, assumedY));

	Motor.rotateF(-Motor.movedRotation);
}

int8_t si = 1;
void ballSearch() {
	Led.setModes(Pattern::flash, 0, Pattern::flash << 1);
	Motor.movedRotation = 0;

	Motor.setSpeeds(100, 90);
#define START_X	-100
#define START_Y -50
	positionInCenter(START_X, START_Y);

	Motor.continuousMode(0, 5);

	bool hasBall = false;
	while(!hasBall) {
		Laser.pingAndWait();
		if(Laser.hitData.hitStatus < 0) {
			hasBall = snatchBall();
			Motor.continuousMode(0, 3);
		}
	}
	Motor.setSpeeds(100, 90);
	Motor.rotateF(-Motor.movedRotation);

	Laser.setArmMode(RAISED_OPEN);
	Led.setModes(0b010000010000, 0b000100000100, 0b000001000001);
	setMotors(false);
	while(1) {
	}
}

}
}


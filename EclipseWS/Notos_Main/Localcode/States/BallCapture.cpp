/*
 * BallCapture.cpp
 *
 *  Created on: 20.04.2017
 *      Author: xasin
 */

#include "BallCapture.h"
#include <math.h>

namespace State {
namespace Ball {

using namespace Robot;
using Communication::Pattern;

Coords assumedPosition;

Coords getCornerPosition(uint8_t c) {
	switch(c) {
	case 0:
		return {COURSE_SIZE_X/2 - CORNER_INSET, COURSE_SIZE_Y/2 - CORNER_INSET};
	case 1:
		return {COURSE_SIZE_X/2 - CORNER_INSET, -COURSE_SIZE_Y/2 + CORNER_INSET};
	case 2:
		return {-COURSE_SIZE_X/2 + CORNER_INSET, -COURSE_SIZE_Y/2 + CORNER_INSET};
	default:
	case 3:
		return {-COURSE_SIZE_X/2 + CORNER_INSET, COURSE_SIZE_Y/2 -CORNER_INSET};
	}
}

void rotateTowards(float direction) {
	Motor.setRotationSpeed(90);
	direction = direction;

	float posTravel = (direction - Motor.movedRotation)%360;
	if(posTravel < 180) {
		Motor.rotateF(posTravel);
	}
	else
		Motor.rotateF(posTravel-360);
}


void moveToPosition(Coords position) {
	Motor.setSpeeds(100, 90);

	rotateTowards(atan2(position.x - assumedPosition.x, position.y - assumedPosition.y) / M_PI * 180);
	Motor.moveF(hypot(position.x - assumedPosition.x, position.y - assumedPosition.y));

	assumedPosition = position;
}


void alignWithWall(uint8_t n) {
	Motor.setSpeeds(100, 90);

	rotateTowards(n*90);

	Motor.continuousMode(100, 0);

	while(!getBumper()) {}
	Motor.cancel();

	Motor.setSpeeds(100, 90);
	Motor.moveF(20);

	switch(n) {
	case 0:
		assumedPosition.y = COURSE_SIZE_Y/2;
	break;

	case 1:
		assumedPosition.x = COURSE_SIZE_X/2;
	break;

	case 2:
		assumedPosition.y = -COURSE_SIZE_Y/2;
	break;

	default:
	case 3:
		assumedPosition.x = -COURSE_SIZE_X/2;
	break;
	}
}


bool checkBlackCorner(uint8_t n) {
	// Initial wall-contact
	alignWithWall(n);

	// 90° rotation, then attempt to drive into the edge
	Motor.setSpeeds(150, 90);
	Motor.moveF(-150);
	Motor.rotateF(90);

	Motor.continuousMode(40, 0);
	while(1) {
		if(getBumper())
			return false;
		if(getBallBoop())
			return true;
	}
}

uint8_t cornerNum = 0;
void getBlackCorner() {
	Laser.setArmMode(RETRACTED);

	while(cornerNum != 4) {
		if(checkBlackCorner(cornerNum))
			break;
		cornerNum++;
	}

	Motor.cancel();
	Motor.setSpeeds(100, 90);

	assumedPosition = getCornerPosition(cornerNum);
}

bool snatchBall() {
	Motor.cancel();
	Laser.setArmMode(RAISED_OPEN);

	Motor.movedDistance = 0;
	Motor.setSpeeds(35, 0);
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
	Motor.setSpeeds(150, 90);

	if(!hasBall) {
		Motor.moveF(-Motor.movedDistance);

		return false;
	}
	else {
		Motor.rotateF(-35);

		Motor.moveBy(-20);
		Laser.setArmMode(LOWERED_OPEN);
		_delay_ms(400);
		Motor.moveBy(20);
		Laser.setArmMode(RAISED_CLOSED);
		_delay_ms(400);

		Motor.rotateF(35);
		Motor.moveF(-Motor.movedDistance);

		return true;
	}
}

float lastRotation = 0;
bool searchForBalls() {
	Motor.setSpeeds(0, 80);
	rotateTowards(lastRotation);

	Motor.continuousMode(0, 5);

	bool hasBall = false;
	while(!hasBall) {
		Laser.pingAndWait();
		if(Laser.hitData.hitStatus < 0) {
			hasBall = snatchBall();
			Motor.continuousMode(0, 5);
		}
	}

	lastRotation = Motor.movedRotation - 10;
	return true;
}

void depositBall() {
	moveToPosition(getCornerPosition(cornerNum));

	float formerRotation = Motor.movedRotation;
	rotateTowards(45 + 90*cornerNum);

	Laser.setArmMode(RAISED_OPEN);
	_delay_ms(300);

	rotateTowards(formerRotation);
	Motor.moveF(-Motor.movedDistance);
	assumedPosition = {0, 0};
}

void ballSearch() {
	Led.setModes(Pattern::flash, 0, Pattern::flash << 1);
	Motor.movedRotation = 0;

	Motor.setSpeeds(100, 90);

	assumedPosition = {START_X, START_Y};

	//getBlackCorner();

	moveToPosition({0, 0});

	while(1) {
		searchForBalls();
		depositBall();
	}

	Laser.setArmMode(RAISED_OPEN);
	Led.setModes(0b010000010000, 0b000100000100, 0b000001000001);
	setMotors(false);
	while(1) {
	}
}

}
}

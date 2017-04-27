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

	float posTravel = fmod((direction - Motor.movedRotation), 360);
	if(posTravel < 0)
		posTravel += 360;

	if(posTravel < 180) {
		Motor.rotateF(posTravel);
	}
	else
		Motor.rotateF(posTravel-360);

	Motor.movedRotation = direction;
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
	Laser.setArmMode(RETRACTED);

	Motor.continuousMode(100, 0);

	while(!getBumper()) {}
	Motor.cancel();

	Motor.setSpeeds(100, 90);
	Motor.moveF(50);

	switch(n%4) {
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

void alignAndReturn(uint8_t n) {
	alignWithWall(n);

	switch(n%2) {
	case 0:
		Motor.moveF(-COURSE_SIZE_Y/2);
		assumedPosition.y = 0;
	break;

	case 1:
		Motor.moveF(-COURSE_SIZE_X/2);
		assumedPosition.x = 0;
	break;
	}

	Motor.movedDistance = 0;
}

bool checkBlackCorner(uint8_t n) {
	moveToPosition(getCornerPosition(n));
	rotateTowards(45 + 90*n);

	Motor.moveBy(100);
	while(1) {
		if(getBumper()) {
			Motor.flush();
			Motor.moveF(-CORNER_BUMP_LENGTH);
			return true;
		}
		if(Motor.isReady()) {
			Motor.moveF(-50);
			return false;
		}
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
uint8_t checkWall = 0;
uint8_t lastBallWall = 0;
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

		if(Motor.movedRotation > (checkWall * 90 + 10)) {
			if(checkWall >= lastBallWall + 4)
				return false;
			alignAndReturn(checkWall++);
			Motor.continuousMode(0, 5);
		}
	}

	lastBallWall = checkWall;
	lastRotation = Motor.movedRotation - 10;
	return true;
}

void depositBall() {
	moveToPosition(getCornerPosition(cornerNum));
	float formerMovement = Motor.movedDistance;
	float formerRotation = Motor.movedRotation;

	rotateTowards(45 + 90*cornerNum);
	Motor.continuousMode(100, 0);

	while(!getBumper()) {}

	Motor.cancel();

	Laser.setArmMode(RAISED_OPEN);
	_delay_ms(300);

	Motor.moveF(-CORNER_BUMP_LENGTH);

	rotateTowards(formerRotation);
	Motor.moveF(-formerMovement);

	Motor.movedDistance = 0;
	assumedPosition = {0, 0};
}

void ballSearch() {
	Led.setModes(Pattern::flash, 0, Pattern::flash << 1);
	Motor.movedRotation = 0;

	Motor.setSpeeds(100, 90);

	assumedPosition = {START_X, START_Y};

	moveToPosition({0, 0});

	getBlackCorner();

	moveToPosition({0, 0});
	rotateTowards(0);
	Motor.movedDistance = 0;

	while(1) {
		if(!searchForBalls())
			break;
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

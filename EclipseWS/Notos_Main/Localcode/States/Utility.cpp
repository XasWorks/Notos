/*
 * Utility.cpp
 *
 *  Created on: 14.02.2017
 *      Author: xasin
 */

#include "Utility.h"

namespace State {
namespace Utility {

using namespace Robot;
using Communication::Pattern;

bool checkForLine(int8_t dir) {
	Motor.rotateBy(70 * dir);
	while(!Motor.isReady()) {
		if(LSensor.lineStatus != LF::Status::LOST)
			return true;
	}

	Motor.rotateBy(-70 * dir);
	Motor.flush();
	return false;

}

void sensitiveSituation() {
	if(!Sensor::Tilting::isTilted())
		return;

	Led.setModes(Pattern::blink, 0, Pattern::blink);

	Motor.setRotationSpeed(0);
	Motor.setSpeed(SLOW_MOTOR_SPEED);
	while(Sensor::Tilting::isTilted()) {

		if(getGroundConductive()) {
			stateFunction = &Ball::ballSearch;
			return;
		}

		_delay_ms(1);
		if(!Sensor::Tilting::isTilted()) {
			Motor.moveBy(50);
			while(!Motor.atPosition()) {
				if(getGroundConductive()) {
					Motor.cancel();
					stateFunction = &Ball::ballSearch;
					return;
				}
			}
			Motor.continuousMode();
		}
	}

	Motor.setRotationSpeed(90);

	if(LSensor.lineStatus != LF::Status::LOST)
		return;
	else if(checkForLine(1)) {}
	else
		checkForLine(-1);

	Motor.continuousMode();
}

void buttonPause() {
	if(!getButton())
		return;

	setMotors(false);

	Led.setModes(0, 0, Pattern::slowblink);
	_delay_ms(1000);

	while(!getButton()) {
		_delay_ms(100);
	}
	_delay_ms(400);

	setMotors(true);
}

void avoidObject() {
	if(!getBumper())
		return;

	Led.setModes(0, Pattern::quickblink, Pattern::quickblink);

	while(!getBumper()) {}

	Motor.setSpeed(120);
	Motor.setRotationSpeed(70);

	Motor.moveBy(-20);
	Motor.flush();
	Motor.rotateBy(90 * AVOID_TURN_DIR);
	Motor.flush();


	Motor.setSpeed(CIRCLE_MOV_SPEED);
	Motor.setRotationSpeed(CIRCLE_DEG_SPEED * -AVOID_TURN_DIR);
	Motor.continuousMode();

	while(LSensor.lineStatus == LF::Status::LOST) {
		_delay_ms(20);
	}

	Motor.setSpeed(120);
	Motor.setRotationSpeed(70);

	Motor.moveBy(50);
	Motor.flush();
	Motor.rotateBy(90 * AVOID_TURN_DIR);
	Motor.flush();

	Motor.continuousMode();
}

void pack() {
	buttonPause();
	sensitiveSituation();
	avoidObject();
}

}
}

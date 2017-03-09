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

void sensitiveSituation() {
	if(!Sensor::Tilting::isTilted())
		return;

	Led.setModes(Pattern::blink, 0, Pattern::blink);

	Motor.setRotationSpeed(0);
	Motor.setSpeed(SLOW_MOTOR_SPEED);
	while(Sensor::Tilting::isTilted()) {
		_delay_ms(10);
	}

	Motor.moveBy(60);
	Motor.flush();
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
	_delay_ms(1000);

	setMotors(true);
}

void avoidObject() {
	if(!getBumper())
		return;

	Led.setModes(0, Pattern::quickblink, Pattern::quickblink);

	while(!getBumper()) {}

	Motor.setSpeed(120);
	Motor.setRotationSpeed(70);

	Motor.moveBy(-50);
	Motor.flush();
	Motor.rotateBy(90 * AVOID_TURN_DIR);
	Motor.flush();
	Motor.moveBy(150);
	Motor.flush();
	Motor.rotateBy(-90 * AVOID_TURN_DIR);
	Motor.flush();

	Motor.moveBy(320);
	Motor.flush();

	Motor.rotateBy(-90 * AVOID_TURN_DIR);
	Motor.flush();

	Motor.setRotationSpeed(0);
	Motor.setSpeed(100);
	Motor.continuousMode();
	while(LSensor.lineStatus == LF::Status::LOST) {}

	Motor.setRotationSpeed(100);
	Motor.moveBy(50);
	Motor.flush();
	Motor.rotateBy(110 * AVOID_TURN_DIR);
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

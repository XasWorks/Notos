/*
 * LineFollow.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: xasin
 */

#include "LineFollow.h"

namespace State {
namespace LineFollow {

using namespace Robot;
using Communication::Pattern;

void ramp() {
	Motor.setRotationSpeed(0);
	Motor.setSpeed(120);

	while(Sensor::Accelleration::isTilted()) {
		_delay_ms(10);
	}
}

void avoidObject() {
	Led.setModes(0, Pattern::flash, Pattern::flash);

	while(!getBumper()) {}

	Motor.setSpeed(120);
	Motor.setRotationSpeed(70);

	Motor.moveBy(-50);
	Motor.flush();
	Motor.rotateBy(90);
	Motor.flush();
	Motor.moveBy(140);
	Motor.flush();
	Motor.rotateBy(-90);
	Motor.flush();

	Motor.moveBy(250);
	Motor.flush();

	Motor.rotateBy(-90);
	Motor.flush();

	Motor.setRotationSpeed(0);
	Motor.setSpeed(100);
	Motor.continuousMode();
	while(LSensor.lineStatus != LF::Status::OK) {}

	Motor.setRotationSpeed(100);
	Motor.moveBy(50);
	Motor.flush();
	Motor.rotateBy(110);
	Motor.flush();

	Motor.continuousMode();
}

void simpleLF() {
	Motor.continuousMode();

	while(true) {
		waitForSensors();

		if(getBumper()) {
			avoidObject();
		}

		if(Sensor::Accelleration::isTilted())
			ramp();

		if(getButton()) {
			setMotors(false);
			Led.setModes(0, 0, Pattern::blink);
			_delay_ms(1000);

			while(!getButton()) {
				_delay_ms(100);
			}
			_delay_ms(1000);

			setMotors(true);
		}

		if(LSensor.lineStatus == LF::Status::OK) {
			Led.setModes(0, Pattern::on, 0);
			Motor.setSpeed(150);
			Motor.setRotationSpeed(-((float)LSensor.lineOffset) * 100 / 127);
		}
		else {
			if(LSensor.lineOffset == 0) {
				Led.setModes(0, 0, Pattern::on);
				Motor.setRotationSpeed(0);
				Motor.setSpeed(100);
			}
			else {
				Led.setModes(Pattern::on, 0, 0);
				Motor.setSpeed(0);
				Motor.setRotationSpeed(LSensor.lineOffset < 0 ? 100 : -100);
			}
		}

	}
}

}
}



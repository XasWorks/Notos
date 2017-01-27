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

void simpleLF() {
	waitForSensors();

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

	Motor.continuousMode();

	if(LSensor.lineStatus == LF::Status::OK) {
		Led.setModes(0, Pattern::quickblink, 0);
		Motor.setSpeed(300);
		Motor.setRotationSpeed(-((float)LSensor.lineOffset) * 150 / 127);
	}
	else {
		if(LSensor.lineOffset == 0) {
			Led.setModes(0, 0, Pattern::on);
			Motor.setRotationSpeed(0);
			Motor.setSpeed(70);
		}
		else {
			Led.setModes(Pattern::on, 0, 0);
			Motor.setSpeed(0);
			Motor.setRotationSpeed(LSensor.lineOffset < 0 ? 150 : -150);
		}
	}
}

}
}



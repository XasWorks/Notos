/*
 * Intersection.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: xasin
 */

#include "Intersection.h"
#include "../../AVR/ADC/ADC_Lib.h"

namespace State {
namespace Intsec {

using namespace Robot;
using Communication::Pattern;

int8_t tDir;

void driveOff(int8_t dir) {
	Motor.setSpeed(120);
	Motor.setRotationSpeed(100);

	Motor.moveBy(27);
	Motor.flush();

	Motor.rotateBy((dir < 0) ? 90 : -90);
	Motor.flush();
}

bool checkDir(int8_t dir) {

	Motor.rotateBy((dir < 0) ? SCAN_ANGLE : -SCAN_ANGLE);
	Motor.flush();
	uint16_t adcValue = ADC_Lib::measure(PINx_GREEN_SENSOR);
	bool status = adcValue > GREEN_THRESHOLD;
	Motor.rotateBy((dir > 0) ? SCAN_ANGLE : -SCAN_ANGLE);
	Motor.flush();

	return status;
}

void runIntsec() {
	Motor.setSpeed(70);
	Motor.setRotationSpeed(50);

	Led.setModes(Pattern::flash, Pattern::flash << 1, 0);

	Motor.moveBy(1);
	Motor.flush();
	_delay_ms(100);

	tDir = LSensor.lineOffset;

	Motor.moveBy(23.5);
	while(!Motor.isReady()) {
		Robot::waitForSensors();
		if(LSensor.lineStatus == LF::Status::INTSEC && LSensor.lineOffset == 0)
			tDir = 0;
		if(Sensor::Tilting::isTilted())
			return;
	}

	if((tDir != 0) && (LSensor.lineStatus == LF::Status::LOST)) {
		driveOff(tDir);
		return;
	}

	if(tDir >= 0)
		if(checkDir(1)) {
			driveOff(1);
			return;
		}
	if(tDir <= 0)
		if(checkDir(-1)) {
			driveOff(-1);
			return;
		}

	Motor.moveBy(20);
	Motor.flush();

}

}
}

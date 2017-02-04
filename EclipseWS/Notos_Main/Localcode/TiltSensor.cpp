/*
 * AccellSensor.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: xasin
 */

#include "TiltSensor.h"
#include "../AVR/ADC/ADC_Lib.h"

namespace Sensor {
namespace Tilting {

uint8_t conseqTriggers;

void initMeasurement() {
	ADC_Lib::start_measurement(PINx_TILT_SENSOR);
}

void analogUpdate() {
	if((ADC_Lib::measuredPin == PINx_TILT_SENSOR)) {
		if((ADC_Lib::lastResult >= TRIGGER_PLUS) || (ADC_Lib::lastResult <= TRIGGER_MINUS)) {
			if(conseqTriggers != CONSECUTIVE_TRIGGERS)
				conseqTriggers++;
		}
		else
			conseqTriggers = 0;

	}
}

bool isTilted() {
	return conseqTriggers >= CONSECUTIVE_TRIGGERS;
}

}
}

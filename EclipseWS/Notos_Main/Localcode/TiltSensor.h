/*
 * AccellSensor.h
 *
 *  Created on: Feb 1, 2017
 *      Author: xasin
 */

#ifndef LOCALCODE_ACCELLSENSOR_H_
#define LOCALCODE_ACCELLSENSOR_H_

#include "Robot.h"

namespace Sensor {
namespace Accelleration {

#define TRIGGER_PLUS 340
#define TRIGGER_MINUS 323

#define CONSECUTIVE_TRIGGERS 5

void initMeasurement();
void analogUpdate();

bool isTilted();

}
}



#endif /* LOCALCODE_ACCELLSENSOR_H_ */

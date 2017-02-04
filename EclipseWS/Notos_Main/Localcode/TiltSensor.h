/*
 * AccellSensor.h
 *
 *  Created on: Feb 1, 2017
 *      Author: xasin
 */

#ifndef LOCALCODE_TILTSENSOR_H_
#define LOCALCODE_TILTSENSOR_H_

#include "Robot.h"

namespace Sensor {
namespace Tilting {

#define TRIGGER_PLUS 500
#define TRIGGER_MINUS 350

#define CONSECUTIVE_TRIGGERS 4

void initMeasurement();
void analogUpdate();

bool isTilted();

}
}



#endif /* LOCALCODE_TILTSENSOR_H_ */

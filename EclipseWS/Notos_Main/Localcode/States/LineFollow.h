/*
 * LineFollow.h
 *
 *  Created on: Jan 27, 2017
 *      Author: xasin
 */

#ifndef LOCALCODE_STATES_LINEFOLLOW_H_
#define LOCALCODE_STATES_LINEFOLLOW_H_

#include "../Robot.h"
#include "../../main.h"

#define MAX_MOTOR_SPEED 	250
#define MIN_MOTOR_SPEED		200
#define MAX_ROTATION_SPEED 	300

#define LINE_CENTERED_CUTOFF 30

namespace State {
namespace LineFollow {

void simpleLF();
void avoidObject();

}
}



#endif /* LOCALCODE_STATES_LINEFOLLOW_H_ */

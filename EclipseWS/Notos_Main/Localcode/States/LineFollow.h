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

#define MAX_MOTOR_SPEED 	450
#define MID_MOTOR_SPEED		250
#define MIN_MOTOR_SPEED		180

#define MAX_ROTATION_SPEED 	230

#define LINE_CENTERED_CUTOFF 	25


namespace State {
namespace LineFollow {

void simpleLF();

}
}



#endif /* LOCALCODE_STATES_LINEFOLLOW_H_ */

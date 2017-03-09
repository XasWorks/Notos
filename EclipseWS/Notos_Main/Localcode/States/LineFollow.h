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

#define MAX_MOTOR_SPEED 	150
#define MID_MOTOR_SPEED		100
#define MIN_MOTOR_SPEED		50

#define MAX_ROTATION_SPEED 	140

#define LINE_CENTERED_CUTOFF 	25


namespace State {
namespace LineFollow {

void simpleLF();

}
}



#endif /* LOCALCODE_STATES_LINEFOLLOW_H_ */

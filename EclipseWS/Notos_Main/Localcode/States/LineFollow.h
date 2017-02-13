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

#define MAX_MOTOR_SPEED 	400
#define MID_MOTOR_SPEED		250
#define MIN_MOTOR_SPEED		150

#define MAX_ROTATION_SPEED 	230

#define LINE_CENTERED_CUTOFF 	20


namespace State {
namespace LineFollow {

void simpleLF();
void avoidObject();

}
}



#endif /* LOCALCODE_STATES_LINEFOLLOW_H_ */

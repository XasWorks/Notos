/*
 * Utility.h
 *
 *  Created on: 14.02.2017
 *      Author: xasin
 */

#ifndef LOCALCODE_STATES_UTILITY_H_
#define LOCALCODE_STATES_UTILITY_H_

#include "../Robot.h"

#define SLOW_MOTOR_SPEED 100

#define AVOID_TURN_DIR -1

#define CIRCLE_RADIUS 140.0
#define CIRCLE_CIRCUMF (CIRCLE_RADIUS * 2 * 3.14)
#define CIRCLE_DEG_LEN (CIRCLE_CIRCUMF / 360.0)

#define CIRCLE_MOV_SPEED 50.0
#define CIRCLE_DEG_SPEED (CIRCLE_MOV_SPEED / CIRCLE_DEG_LEN)

namespace State {
namespace Utility {

void sensitiveSituation();
void buttonPause();
void avoidObject();

void pack();

}
}


#endif /* LOCALCODE_STATES_UTILITY_H_ */

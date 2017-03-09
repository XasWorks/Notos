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

namespace State {
namespace Utility {

void sensitiveSituation();
void buttonPause();
void avoidObject();

void pack();

}
}


#endif /* LOCALCODE_STATES_UTILITY_H_ */

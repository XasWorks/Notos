/*
 * BallCapture.h
 *
 *  Created on: 20.04.2017
 *      Author: xasin
 */

#ifndef LOCALCODE_STATES_BALLCAPTURE_H_
#define LOCALCODE_STATES_BALLCAPTURE_H_

#include "../../main.h"
#include <math.h>

#define FRONT_TO_CENTER 10

#define CORNER_INSET		300
#define COURSE_SIZE_X 	(1200 - 2*FRONT_TO_CENTER)
#define COURSE_SIZE_Y 	(900  - 2*FRONT_TO_CENTER)

#define START_X	-150
#define START_Y	-450

namespace State {
namespace Ball {

struct Coords {
	float x;
	float y;
};


	void ballSearch();
}
}


#endif /* LOCALCODE_STATES_BALLCAPTURE_H_ */

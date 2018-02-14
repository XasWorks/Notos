/*
 * LineFollow.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: xasin
 */

#include "LineFollow.h"
#include "Utility.h"
#include "Intersection.h"
#include "BallCapture.h"


namespace State {
namespace LineFollow {

using namespace Robot;
using Communication::Pattern;

void simpleLF() {
	Motor.continuousMode();

	while(true) {
		waitForSensors();

		Utility::pack();

		if(getGroundConductive()) {
			stateFunction = &Ball::ballSearch;
			return;
		}

		// Normales Line-Following
		if(LSensor.lineStatus == LF::Status::OK) {
			Led.setModes(0, Pattern::on, 0);		// Grünes Status-Licht
			// Motorgeschwindigkeit "zweifach" proportional abhängig zwischen 0-LINE_CENTERED_CUTOFF und LCC-127
			// Dies sorgt für High-Speed bei gerader Strecke, und feinen, problemlosen Kurven
			Motor.setSpeed(fmax(					//
			MID_MOTOR_SPEED - (MID_MOTOR_SPEED - MIN_MOTOR_SPEED) * fabs(LSensor.lineOffset)/127,
			MAX_MOTOR_SPEED - (MAX_MOTOR_SPEED - MID_MOTOR_SPEED) * fabs(LSensor.lineOffset)/LINE_CENTERED_CUTOFF));

			// Rotationsgeschwindigkeit proportional abhängig von der Auslenkung der Linie
			Motor.setRotationSpeed(-((float)LSensor.lineOffset) * MAX_ROTATION_SPEED / 127);
		}
		// "Event"-Handling für das Verlieren der Linie
		else if(LSensor.lineStatus == LF::Status::LOST) {
			if(LSensor.lineOffset < LINE_CENTERED_CUTOFF && LSensor.lineOffset > -LINE_CENTERED_CUTOFF) {
				Led.setModes(0, 0, Pattern::blink);
				Motor.setRotationSpeed(0);
				Motor.setSpeed(MID_MOTOR_SPEED);
			}
			else {
				Led.setModes(Pattern::on, 0, 0);
				Motor.setSpeed(0);
				Motor.setRotationSpeed(MAX_ROTATION_SPEED * (LSensor.lineOffset < 0 ? 1 : -1));
			}
		}
		else {
			Intsec::runIntsec();
			return;
		}
	}
}

}
}

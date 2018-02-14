/*
 * USB.cpp
 *
 *  Created on: 25.01.2017
 *      Author: xasin
 */

#include "USB.h"
#include "BallCapture.h"

namespace State {
namespace USB {

using namespace Robot;
using Communication::Pattern;

void simpleDebug() {
	Led.setModes(0, 0b11, 0);

	_delay_ms(100);

	if(LSensor.lineStatus != LF::Status::OK) {
		switch(LSensor.lineStatus) {
		case LF::Status::LOST:
			Led.signal(0b1001, 0b011, 0b1, 6);
		break;

		case LF::Status::INTSEC:
			Led.signal(0b1, 0b011, 0b1001, 6);
		break;

		default:
			Led.signal(0b1, 0b11, 0b1, 6);
		break;
		}
	}

	if(getBumper())
		Led.signal(0b11, 0b1, 0b1011, 6);
	if(getGroundConductive())
		Led.signal(0b11, 0b1001, 0b11, 6);
	if(getBallBoop())
		Led.signal(0b11, 0b1001, 0b1011, 6);

	if(Sensor::Tilting::isTilted())
		Led.signal(0b1011, 0b1, 0b11, 6);

	Laser.ping();
	if(!Laser.isPresent)
		Led.signal(0b11111, 0b111, 0b111, 5);
	else if(Laser.hitData.hitStatus < 0)
		Led.signal(0b111, 0b111, 0b111, 6);
}

}
}

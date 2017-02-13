/*
 * USB.cpp
 *
 *  Created on: 25.01.2017
 *      Author: xasin
 */

#include "USB.h"

namespace State {
namespace USB {

using namespace Robot;
using Communication::Pattern;

void simpleDebug() {
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

	if(Sensor::Tilting::isTilted())
		Led.signal(0b1011, 0b1, 0b11, 6);

	Led.setModes(0, 0b11, 0);
}

}
}


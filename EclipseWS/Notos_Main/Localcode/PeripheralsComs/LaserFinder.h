/*
 * LaserFinder.h
 *
 *  Created on: 05.04.2017
 *      Author: xasin
 */

#ifndef LOCALCODE_PERIPHERALSCOMS_LASERFINDER_H_
#define LOCALCODE_PERIPHERALSCOMS_LASERFINDER_H_

namespace Peripheral {

class LaserFinder: public TWI::Job {
public:
	LaserFinder();
};

} /* namespace Peripheral */

#endif /* LOCALCODE_PERIPHERALSCOMS_LASERFINDER_H_ */

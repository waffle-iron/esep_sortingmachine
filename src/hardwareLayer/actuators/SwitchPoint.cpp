/*
 * SwitchPoint.cpp
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include "SwitchPoint.h"
#include "GPIO.h"
#include "Header.h"

constexpr port_t SWITCHPOINT_OPEN = 0b00010000;

namespace hardwareLayer {
namespace actuators {


	SwitchPoint& SwitchPoint::instance() {
		static SwitchPoint instance;
		return instance;
	}

	SwitchPoint::SwitchPoint() {
		LOG_SCOPE;
	}

	SwitchPoint::~SwitchPoint() {
		LOG_SCOPE;
	}

	void SwitchPoint::open(){
		io::GPIO::instance().setBits(PORT::A,  SWITCHPOINT_OPEN);
	}

	void SwitchPoint::close(){
		io::GPIO::instance().clearBits(PORT::A,  SWITCHPOINT_OPEN);
	}


} /* namespace actuators */
} /* namespace hal */

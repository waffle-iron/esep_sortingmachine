/*
 * ButtonLEDs.cpp
 *
 *  Created on: 10.11.2017
 *      Author: aca311
 */

#include "ButtonLEDs.h"
#include "header.h"


namespace hardwareLayer {
namespace mmi {

ButtonLEDs& ButtonLEDs::instance() {
	static ButtonLEDs instance;
	return instance;
}


ButtonLEDs::ButtonLEDs() {
	LOG_SCOPE;
}

ButtonLEDs::~ButtonLEDs() {
	LOG_SCOPE;
}

} /* namespace mmi */
} /* namespace hal */


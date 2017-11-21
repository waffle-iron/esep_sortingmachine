/*
 * Timer.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: stammtisch
 */

#include "Timer.h"
#include "Header.h"

namespace logicLayer {

Timer::Timer(hardwareLayer::HardwareLayer& hal)
: hal(hal)
{
	// TODO Auto-generated constructor stub

}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::start_chatter_timer() {
	WAIT(100);
	hal.pollOnSensors();
}

} /* namespace logicLayer */

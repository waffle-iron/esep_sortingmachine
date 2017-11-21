/*
 * Timer.h
 *
 *  Created on: Nov 21, 2017
 *      Author: stammtisch
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "HardwareLayer.h"

namespace logicLayer {

class Timer {
public:
	Timer(hardwareLayer::HardwareLayer& hal);
	virtual ~Timer();

	void start_chatter_timer();

private:
	hardwareLayer::HardwareLayer& hal;
};

} /* namespace logicLayer */
#endif /* TIMER_H_ */

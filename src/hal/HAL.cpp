/*
 * HardwareAbstractionLayer.cpp
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include "HAL.h"
#include "Motor.h"

namespace hal {

HAL::HAL() {
	// TODO Auto-generated constructor stub

}

HAL::~HAL() {
	// TODO Auto-generated destructor stub
}

void HAL::motorStart() {
	hal::actuators::Motor::instance()->start();
}

}

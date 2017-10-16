/*
 * HardwareAbstractionLayer.cpp
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include "HAL.h"

namespace hal {

HAL::HAL() {
	_motor = actuators::Motor::instance();

}

HAL::~HAL() {
	// TODO Auto-generated destructor stub
}

void HAL::motorStart() {
	_motor->start();
}

}

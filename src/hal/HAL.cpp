/*
 * HardwareAbstractionLayer.cpp
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include "HAL.h"
#include "GPIO.h"

namespace hal {

HAL::HAL() {
	_motor = actuators::Motor::instance();
	_switchpoint = actuators::Switchpoint::instance();
}

HAL::~HAL() {
	delete _motor;
	delete io::GPIO::instance();
}

void HAL::motorStart() {
	_motor->start();
}

void HAL::motorRotateClockwise() {
	_motor->setClockwiseRotation();
}

void HAL::switchPointOpen(){
	_switchpoint->open();
}

void HAL::switchPointClose(){
	_switchpoint->close();
}

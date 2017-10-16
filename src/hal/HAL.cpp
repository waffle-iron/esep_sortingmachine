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
	_switchPoint = actuators::SwitchPoint::instance();
	_trafficLight = io::TrafficLight::instacne();
}

HAL::~HAL() {
	delete _motor;
	delete io::GPIO::instance();
}

void HAL::motorStart() {
	_motor->start();
}

void HAL::motorStop() {
	_motor->stop();
}

void HAL::motorSlow() {
	_motor->setSlow();
}

void HAL::motorFast() {
	_motor->clearSlow();
}

void HAL::motorRotateClockwise() {
	_motor->setClockwiseRotation();
}

void HAL::switchPointOpen(){
	_switchPoint->open();
}

void HAL::switchPointClose(){
	_switchPoint->close();
}

} /* hal */

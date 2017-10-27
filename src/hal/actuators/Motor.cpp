/*
 * Motor.cpp
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include "Motor.h"
#include "GPIO.h"
#include "Header.h"

constexpr port_t CLOCKWISE_ROTATION 		= 0b00000001;
constexpr port_t COUNTERCLOCKWISE_ROTATION 	= 0b00000010;
constexpr port_t MOTOR_SLOW					= 0b00000100;
constexpr port_t MOTOR_STOP 				= 0b00001000;

namespace hal {
namespace actuators {

Motor *Motor::_instance = nullptr;

Motor *Motor::instance() {
	if (_instance == nullptr) {
		_instance = new Motor;
	}
	return _instance;
}

Motor::Motor() {
	LOG_SCOPE;
}

Motor::~Motor() {
	LOG_SCOPE;
	_instance = nullptr;
}

void Motor::start() {
	io::GPIO::instance()->clearBits(PORT::A, MOTOR_STOP);
}

void Motor::stop() {
	io::GPIO::instance()->setBits(PORT::A, MOTOR_STOP);
}

void Motor::setSlow() {
	io::GPIO::instance()->setBits(PORT::A, MOTOR_SLOW);
}

void Motor::clearSlow() {
	io::GPIO::instance()->clearBits(PORT::A, MOTOR_SLOW);
}

void Motor::setClockwiseRotation() {
	io::GPIO::instance()->clearBits(PORT::A, COUNTERCLOCKWISE_ROTATION);
	io::GPIO::instance()->setBits(PORT::A, CLOCKWISE_ROTATION);
}

void Motor::setCounterclockwiseRotation() {
	io::GPIO::instance()->clearBits(PORT::A, CLOCKWISE_ROTATION);
	io::GPIO::instance()->setBits(PORT::A, COUNTERCLOCKWISE_ROTATION);
}

} /* namespace actuators */
} /* namespace hal */


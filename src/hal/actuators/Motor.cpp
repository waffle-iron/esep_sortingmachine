/*
 * Motor.cpp
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include "Motor.h"
#include "GPIO.h"

constexpr int CLOCKWISE_ROTATION 	= 0b00000001;
constexpr int MOTOR_START 			= 0b00001000;

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
	// TODO Auto-generated constructor stub

}

Motor::~Motor() {
	delete _instance;
}

void Motor::start() {
	int port_a = io::GPIO::instance()->read(PORT::A);
	io::GPIO::instance()->write(PORT::A, port_a & ~MOTOR_START);
}

void Motor::setClockwiseRotation() {
//	int storedPortValue = io::GPIO::instance()->read(PORT::A);
//	io::GPIO::instance()->write(PORT::A, storedPortValue | CLOCKWISE_ROTATION);
	io::GPIO::instance()->setBits(PORT::A, CLOCKWISE_ROTATION);
}

} /* namespace actuators */
} /* namespace hal */


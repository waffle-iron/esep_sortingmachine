/*
 * Motor.cpp
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include "Motor.h"
#include "GPIO.h"

#define _BV(x) (1<<(x))
#define LIGHT_GREEN 5

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
	io::GPIO::instance()->write(PORT::A, _BV(LIGHT_GREEN));
}

} /* namespace actuators */
} /* namespace hal */


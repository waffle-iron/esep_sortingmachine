/*
 * TrafficLights.cpp
 *
 *  Created on: 16.10.2017
 *      Author: aca311
 */

#include "TrafficLight.h"

namespace hal {
namespace io {

TrafficLight *TrafficLight::_instance = nullptr;

TrafficLight *TrafficLights::instance() {
	if (_instance == nullptr) {
		_instance = new TrafficLight;
	}
	return _instance;
}

Motor::Motor() {
	// TODO Auto-generated constructor stub

}

Motor::~Motor() {
	delete _instance;
}

} /* namespace io */
} /* namespace hal */

/*
 * TrafficLights.cpp
 *
 *  Created on: 16.10.2017
 *      Author: aca311
 */

#include "TrafficLight.h"

namespace hal {
namespace io {
constexpr int PIN_RED_LIGHT = 7;
constexpr int PIN_YELLOW_LIGHT = 6;
constexpr int PIN_GREEN_LIGHT = 5;

constexpr int PORT_A_ADDR = 0x300;


TrafficLight *TrafficLight::_instance = nullptr;

TrafficLight *TrafficLight::instance() {
	if (_instance == nullptr) {
		_instance = new TrafficLight;
	}
	return _instance;
}

TrafficLight::TrafficLight() {
	// TODO Auto-generated constructor stub

}

TrafficLight::~TrafficLight() {
	delete _instance;
}

} /* namespace io */
} /* namespace hal */

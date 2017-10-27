/*
 * TrafficLights.cpp
 *
 *  Created on: 16.10.2017
 *      Author: aca311
 */

#include "TrafficLight.h"
#include <iostream>
#include "Header.h"

namespace hal {
namespace mmi {

constexpr port_t PIN_GREEN_LIGHT 	= 0x20;
constexpr port_t PIN_YELLOW_LIGHT 	= 0x40;
constexpr port_t PIN_RED_LIGHT 		= 0x80;


TrafficLight& TrafficLight::instance() {
	static TrafficLight instance;
	return instance;
}

TrafficLight::TrafficLight() {
	LOG_SCOPE;
	blink = mmi::Blink();
	thread = std::thread(std::ref(blink));
}

TrafficLight::~TrafficLight() {
	LOG_SCOPE;
	blink.terminate();
	thread.join();
}

void TrafficLight::greenLightOn() {
	blink.removeBitmask(PIN_GREEN_LIGHT);
	io::GPIO::instance().setBits(PORT::A, PIN_GREEN_LIGHT);
}

void TrafficLight::yellowLightOn() {
	blink.removeBitmask(PIN_YELLOW_LIGHT);
	io::GPIO::instance().setBits(PORT::A, PIN_YELLOW_LIGHT);
}

void TrafficLight::redLightOn() {
	blink.removeBitmask(PIN_RED_LIGHT);
	io::GPIO::instance().setBits(PORT::A, PIN_RED_LIGHT);
}

void TrafficLight::greenLightOff() {
	blink.removeBitmask(PIN_GREEN_LIGHT);
	io::GPIO::instance().clearBits(PORT::A, PIN_GREEN_LIGHT);
}

void TrafficLight::yellowLightOff() {
	blink.removeBitmask(PIN_YELLOW_LIGHT);
	io::GPIO::instance().clearBits(PORT::A, PIN_YELLOW_LIGHT);
}

void TrafficLight::redLightOff() {
	blink.removeBitmask(PIN_RED_LIGHT);
	io::GPIO::instance().clearBits(PORT::A, PIN_RED_LIGHT);
}


void TrafficLight::blinkGreen(Speed speed) {
	blink.add(PIN_GREEN_LIGHT, speed);
}

void TrafficLight::blinkYellow(Speed speed) {
	blink.add(PIN_YELLOW_LIGHT, speed);
}

void TrafficLight::blinkRed(Speed speed) {
	blink.add(PIN_RED_LIGHT, speed);
}

} /* namespace hmi */
} /* namespace hal */

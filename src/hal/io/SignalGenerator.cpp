/*
 * InterruptHandler.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: stammtisch
 */

#include "SignalGenerator.h"
#include "Header.h"
#include "AsyncChannel.h"
#include "ISR.h"
#include <iostream>
#include "GPIO.h"
#include <map>

constexpr int MAGIC_NUMBER = 15;

const map<const Signalname, const int> signals = {
	{Signalname::BUTTON_START_PUSHED,  0b00010000},
	{Signalname::BUTTON_STOP_PUSHED,  !0b00100000},
	{Signalname::BUTTON_RESET_PUSHED,  0b01000000},
	{Signalname::BUTTON_E_STOP_PUSHED,!0b10000000},
	{Signalname::BUTTON_E_STOP_PULLED, 0b10000000},
	{Signalname::LIGHT_BARRIER_INPUT_INTERRUPTED,  	  !0b00000001},
	{Signalname::LIGHT_BARRIER_INPUT_NOT_INTERRUPTED,  0b00000001},
	{Signalname::LIGHT_BARRIER_HEIGHT_INTERRUPTED,    !0b00000010},
	{Signalname::LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED, 0b00000010},
	{Signalname::LIGHT_BARRIER_SWITCH_INTERRUPTED,    !0b00001000},
	{Signalname::LIGHT_BARRIER_SWITCH_NOT_INTERRUPTED, 0b00001000},
	{Signalname::LIGHT_BARRIER_SLIDE_INTERRUPTED,     !0b00100000},
	{Signalname::LIGHT_BARRIER_SLIDE_NOT_INTERRUPTED,  0b00100000},
	{Signalname::LIGHT_BARRIER_OUTPUT_INTERRUPTED,    !0b10000000},
	{Signalname::LIGHT_BARRIER_OUTPUT_NOT_INTERRUPTED, 0b10000000},
	{Signalname::SENSOR_HEIGHT_MATCH,  		0b00000100},
	{Signalname::SENSOR_HEIGHT_NOT_MATCH,  !0b00000100},
	{Signalname::SENSOR_METAL_MATCH,  		0b00010000},
	{Signalname::SENSOR_METAL_NOT_MATCH,   !0b00010000},
	{Signalname::SENSOR_SWITCH_IS_OPEN,  	0b01000000},
	{Signalname::SENSOR_SWITCH_IS_CLOSED,  !0b01000000},
};


namespace hal {
namespace io {

SignalGenerator::SignalGenerator():
running(true) {
	hal::io::GPIO::instance()->gainAccess(); // first time calling singleton
	ISR::registerISR(AsyncChannel::getChannel(), MAGIC_NUMBER);
	thread = std::thread(std::ref(*this));
}

SignalGenerator::~SignalGenerator() {
	stop();
	AsyncChannel::getChannel().sendMessage({0,0});
	thread.join();
	ISR::unregisterISR();
}

void SignalGenerator::operator()() {
	while (running) {
		AsyncMsg message;
		message = AsyncChannel::getChannel().getNextMessage();
		std::cout << message.value << std::endl;
	}
}

void SignalGenerator::stop() {
	running = false;
}

} /* namespace io */
} /* namespace hal */

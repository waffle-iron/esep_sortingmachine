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

constexpr int MAGIC_NUMBER = 15;


namespace hal {
namespace io {

const map<const int, SPair> SignalGenerator::signals = SignalGenerator::init_map();


SignalGenerator::SignalGenerator():
running(true) {
	LOG_SCOPE
	hal::io::GPIO::instance()->gainAccess();
	stored_mask = hal::io::GPIO::instance()->read(PORT::C)<<8 | hal::io::GPIO::instance()->read(PORT::B);
	ISR::registerISR(AsyncChannel::getChannel(), MAGIC_NUMBER);
	thread = std::thread(std::ref(*this));
}

SignalGenerator::~SignalGenerator() {
	LOG_SCOPE
	stop();
	AsyncChannel::getChannel().sendMessage({0,0});
	thread.join();
	ISR::unregisterISR();
}

void SignalGenerator::operator()() {
	LOG_SCOPE
	while (running) {
		AsyncMsg message;
		message = AsyncChannel::getChannel().getNextMessage();
		int current_mask = message.value;
		int change = current_mask xor stored_mask;
		for(const auto &signal : signals) {
			if (change & signal.first) { // change happend on signal?
				if (signal.first & current_mask) { 	// low -> high
					signalBuffer.push_back(Signal(1,1,signal.second.high));
				} else {						// high -> low
					signalBuffer.push_back(Signal(1,1,signal.second.low));
				}
			}
		}
		stored_mask = current_mask;
	}
}

void SignalGenerator::stop() {
	LOG_SCOPE
	running = false;
}

Signal SignalGenerator::nextSignal() {
	LOG_SCOPE
	Signal signal = signalBuffer.front();
	signalBuffer.erase(signalBuffer.begin());
	return signal;
}

const std::map<const int, SPair> SignalGenerator::init_map() {
	LOG_SCOPE
	map<const int, SPair> map;
	map.insert({0b00010000<<8, SPair(	Signalname::BUTTON_START_PUSHED,
										Signalname::BUTTON_START_PULLED)});
	map.insert({0b00100000<<8, SPair(	Signalname::BUTTON_STOP_PULLED,
										Signalname::BUTTON_STOP_PUSHED)});
	map.insert({0b01000000<<8, SPair(	Signalname::BUTTON_RESET_PUSHED,
										Signalname::BUTTON_RESET_PUSHED)});
	map.insert({0b10000000<<8, SPair(	Signalname::BUTTON_E_STOP_PULLED,
										Signalname::BUTTON_E_STOP_PUSHED)});
	map.insert({0b00000001, SPair(	Signalname::LIGHT_BARRIER_INPUT_NOT_INTERRUPTED,
									Signalname::LIGHT_BARRIER_INPUT_INTERRUPTED)});
	map.insert({AsyncChannel::LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED.bitmask, SPair(	Signalname::LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED,
									Signalname::LIGHT_BARRIER_HEIGHT_INTERRUPTED)});
	map.insert({0b00001000, SPair(	Signalname::LIGHT_BARRIER_SWITCH_NOT_INTERRUPTED,
									Signalname::LIGHT_BARRIER_SWITCH_INTERRUPTED)});
	map.insert({0b00100000, SPair(	Signalname::LIGHT_BARRIER_SLIDE_NOT_INTERRUPTED,
									Signalname::LIGHT_BARRIER_SLIDE_INTERRUPTED)});
	map.insert({0b10000000, SPair( 	Signalname::LIGHT_BARRIER_OUTPUT_NOT_INTERRUPTED,
									Signalname::LIGHT_BARRIER_OUTPUT_INTERRUPTED)});
	map.insert({0b00000100, SPair(	Signalname::SENSOR_HEIGHT_MATCH,
									Signalname::SENSOR_HEIGHT_NOT_MATCH)});
	map.insert({0b00010000, SPair( 	Signalname::SENSOR_METAL_MATCH,
									Signalname::SENSOR_METAL_NOT_MATCH)});
	map.insert({0b01000000, SPair( 	Signalname::SENSOR_SWITCH_IS_OPEN,
									Signalname::SENSOR_SWITCH_IS_CLOSED)});
	return map;
}


} /* namespace io */
} /* namespace hal */
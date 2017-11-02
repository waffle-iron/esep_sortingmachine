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
#include <string>//bugfixing

constexpr int MAGIC_NUMBER = 15;


namespace hal {
namespace io {

SignalBitmask SignalGenerator::BUTTON_START(		0b00010000<<8, "BUTTON_START");
SignalBitmask SignalGenerator::BUTTON_STOP( 		0b00100000<<8, "BUTTON_STOP");
SignalBitmask SignalGenerator::BUTTON_RESET( 		0b01000000<<8, "BUTTON_RESET");
SignalBitmask SignalGenerator::BUTTON_E_STOP(		0b10000000<<8, "BUTTON_E_STOP");
SignalBitmask SignalGenerator::LIGHT_BARRIER_INPUT( 0b00000001, "LIGHT_BARRIER_INPUT");
SignalBitmask SignalGenerator::LIGHT_BARRIER_HEIGHT(0b00000010, "LIGHT_BARRIER_HEIGHT");
SignalBitmask SignalGenerator::SENSOR_HEIGHT_MATCH(	0b00000100, "SENSOR_HEIGHT_MATCH");
SignalBitmask SignalGenerator::LIGHT_BARRIER_SWITCH(0b00001000, "LIGHT_BARRIER_SWITCH");
SignalBitmask SignalGenerator::SENSOR_METAL_MATCH(	0b00010000, "SENSOR_METAL_MATCH");
SignalBitmask SignalGenerator::SENSOR_SWITCH_OPEN(	0b00100000, "SENSOR_SWITCH_OPEN");
SignalBitmask SignalGenerator::LIGHT_BARRIER_SLIDE(	0b01000000, "LIGHT_BARRIER_SLIDE");
SignalBitmask SignalGenerator::LIGHT_BARRIER_OUTPUT(0b10000000, "LIGHT_BARRIER_OUTPUT");

const map<const int, SPair> SignalGenerator::signals = SignalGenerator::init_map();


SignalGenerator::SignalGenerator():
running(true) {
	LOG_SCOPE
	hal::io::GPIO::instance().gainAccess();
	stored_mask = hal::io::GPIO::instance().read(PORT::C)<<8 | hal::io::GPIO::instance().read(PORT::B);
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
		int current_mask = (int)message.value;
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
	Signal signal(0b001,0b000,Signalname::SIGNAL_BUFFER_EMPTY);
	if (not signalBuffer.empty()) {
		signal = signalBuffer.front();
		signalBuffer.erase(signalBuffer.begin());
	}
	return signal;
}

void SignalGenerator::resetSignalBuffer() {
	LOG_SCOPE
	signalBuffer.clear();
	if(signalBuffer.size() != 0){
		LOG_ERROR<<__FUNCTION__<<": could not clear signalBuffer"<<endl;
	}
}

const std::map<const int, SPair> SignalGenerator::init_map() {
	LOG_SCOPE
	map<const int, SPair> map;
	map.insert({BUTTON_START.bitmask, SPair(
				Signalname::BUTTON_START_PUSHED,
				Signalname::BUTTON_START_PULLED)});
	map.insert({BUTTON_STOP.bitmask, SPair(
				Signalname::BUTTON_STOP_PULLED,
				Signalname::BUTTON_STOP_PUSHED)});
	map.insert({BUTTON_RESET.bitmask, SPair(
				Signalname::BUTTON_RESET_PUSHED,
				Signalname::BUTTON_RESET_PULLED)});
	map.insert({BUTTON_E_STOP.bitmask, SPair(
				Signalname::BUTTON_E_STOP_PULLED,
				Signalname::BUTTON_E_STOP_PUSHED)});
	map.insert({LIGHT_BARRIER_INPUT.bitmask, SPair(
				Signalname::LIGHT_BARRIER_INPUT_NOT_INTERRUPTED,
				Signalname::LIGHT_BARRIER_INPUT_INTERRUPTED)});
	map.insert({LIGHT_BARRIER_HEIGHT.bitmask, SPair(
				Signalname::LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED,
				Signalname::LIGHT_BARRIER_HEIGHT_INTERRUPTED)});
	map.insert({LIGHT_BARRIER_SWITCH.bitmask, SPair(
				Signalname::LIGHT_BARRIER_SWITCH_NOT_INTERRUPTED,
				Signalname::LIGHT_BARRIER_SWITCH_INTERRUPTED)});
	map.insert({LIGHT_BARRIER_SLIDE.bitmask, SPair(
				Signalname::LIGHT_BARRIER_SLIDE_NOT_INTERRUPTED,
				Signalname::LIGHT_BARRIER_SLIDE_INTERRUPTED)});
	map.insert({LIGHT_BARRIER_OUTPUT.bitmask, SPair(
				Signalname::LIGHT_BARRIER_OUTPUT_NOT_INTERRUPTED,
				Signalname::LIGHT_BARRIER_OUTPUT_INTERRUPTED)});
	map.insert({SENSOR_HEIGHT_MATCH.bitmask, SPair(
				Signalname::SENSOR_HEIGHT_MATCH,
				Signalname::SENSOR_HEIGHT_NOT_MATCH)});
	map.insert({SENSOR_METAL_MATCH.bitmask, SPair(
				Signalname::SENSOR_METAL_MATCH,
				Signalname::SENSOR_METAL_NOT_MATCH)});
	map.insert({SENSOR_SWITCH_OPEN.bitmask, SPair(
				Signalname::SENSOR_SWITCH_IS_OPEN,
				Signalname::SENSOR_SWITCH_IS_CLOSED)});
	return map;
}


} /* namespace io */
} /* namespace hal */

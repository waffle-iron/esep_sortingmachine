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

const SensorEvent SignalGenerator::BUTTON_START(		0b00010000<<8, "BUTTON_START", SPair(	  Signalname::BUTTON_START_PUSHED,
				  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	 	  Signalname::BUTTON_START_PULLED));
const SensorEvent SignalGenerator::BUTTON_STOP( 		0b00100000<<8, "BUTTON_STOP", SPair( 	  Signalname::BUTTON_STOP_PULLED,
																							 	  Signalname::BUTTON_STOP_PUSHED));
const SensorEvent SignalGenerator::BUTTON_RESET( 		0b01000000<<8, "BUTTON_RESET", SPair(	  Signalname::BUTTON_RESET_PUSHED,
																								  Signalname::BUTTON_RESET_PULLED));
const SensorEvent SignalGenerator::BUTTON_E_STOP(		0b10000000<<8, "BUTTON_E_STOP", SPair(	  Signalname::BUTTON_E_STOP_PULLED,
																								  Signalname::BUTTON_E_STOP_PUSHED));
const SensorEvent SignalGenerator::LIGHT_BARRIER_INPUT( 0b00000001, "LIGHT_BARRIER_INPUT", SPair( Signalname::LIGHT_BARRIER_INPUT_NOT_INTERRUPTED,
																								  Signalname::LIGHT_BARRIER_INPUT_INTERRUPTED));
const SensorEvent SignalGenerator::LIGHT_BARRIER_HEIGHT(0b00000010, "LIGHT_BARRIER_HEIGHT", SPair(Signalname::LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED,
																								  Signalname::LIGHT_BARRIER_HEIGHT_INTERRUPTED));
const SensorEvent SignalGenerator::SENSOR_HEIGHT_MATCH(	0b00000100, "SENSOR_HEIGHT_MATCH", SPair( Signalname::SENSOR_HEIGHT_MATCH,
																								  Signalname::SENSOR_HEIGHT_NOT_MATCH));
const SensorEvent SignalGenerator::LIGHT_BARRIER_SWITCH(0b00001000, "LIGHT_BARRIER_SWITCH", SPair(Signalname::LIGHT_BARRIER_SWITCH_NOT_INTERRUPTED,
																								  Signalname::LIGHT_BARRIER_SWITCH_INTERRUPTED));
const SensorEvent SignalGenerator::SENSOR_METAL_MATCH(	0b00010000, "SENSOR_METAL_MATCH", SPair(  Signalname::SENSOR_METAL_MATCH,
																								  Signalname::SENSOR_METAL_NOT_MATCH));
const SensorEvent SignalGenerator::SENSOR_SWITCH_OPEN(	0b00100000, "SENSOR_SWITCH_OPEN", SPair(  Signalname::SENSOR_SWITCH_IS_OPEN,
																								  Signalname::SENSOR_SWITCH_IS_CLOSED));
const SensorEvent SignalGenerator::LIGHT_BARRIER_SLIDE(	0b01000000, "LIGHT_BARRIER_SLIDE", SPair( Signalname::LIGHT_BARRIER_SLIDE_NOT_INTERRUPTED,
																								  Signalname::LIGHT_BARRIER_SLIDE_INTERRUPTED));
const SensorEvent SignalGenerator::LIGHT_BARRIER_OUTPUT(0b10000000, "LIGHT_BARRIER_OUTPUT", SPair(Signalname::LIGHT_BARRIER_OUTPUT_NOT_INTERRUPTED,
																								  Signalname::LIGHT_BARRIER_OUTPUT_INTERRUPTED));

const vector<const SensorEvent> SignalGenerator::events = SignalGenerator::init_events();


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
		for(const auto &event : events) {
			if (change & event.bitmask) { // change happend on event?
				if (event.bitmask & current_mask) { 	// low -> high
					signalBuffer.push_back(Signal(1,1,event.signalPair.high));
				} else {						// high -> low
					signalBuffer.push_back(Signal(1,1,event.signalPair.low));
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

const std::vector<const SensorEvent> SignalGenerator::init_events() {
	LOG_SCOPE
	std::vector<const SensorEvent> vector;
	vector.push_back(BUTTON_START);
	vector.push_back(BUTTON_STOP);
	vector.push_back(BUTTON_RESET);
	vector.push_back(BUTTON_E_STOP);
	vector.push_back(LIGHT_BARRIER_INPUT);
	vector.push_back(LIGHT_BARRIER_HEIGHT);
	vector.push_back(LIGHT_BARRIER_SWITCH);
	vector.push_back(LIGHT_BARRIER_SLIDE);
	vector.push_back(LIGHT_BARRIER_OUTPUT);
	vector.push_back(SENSOR_HEIGHT_MATCH);
	vector.push_back(SENSOR_METAL_MATCH);
	vector.push_back(SENSOR_SWITCH_OPEN);
	return vector;
}


} /* namespace io */
} /* namespace hal */

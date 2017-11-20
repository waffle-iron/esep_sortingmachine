/*
 * InterruptHandler.cpp
 *
 *  Created on: 20.10.2017
 *      Author: abj240
 */

#include "SignalGenerator.h"
#include "Header.h"
#include "AsyncChannel.h"
#include "ISR.h"
#include "GPIO.h"
#include <iostream>
#include <iomanip>
#include "Signals.h"

constexpr int MAGIC_NUMBER = 15;


namespace hardwareLayer {
namespace io {


const int NOCLATTER = 0;
const int SWITCH_BUTTON_CLATTER_TIME = 50;
const int E_STOP_CLATTER_TIME = 650;

const SensorEvent SignalGenerator::BUTTON_START(		0b00010000<<8, "BUTTON_START", SWITCH_BUTTON_CLATTER_TIME , SPair(	Signalname::BUTTON_START_PUSHED,
				  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	 	  	  	  	  	  	  	  	Signalname::BUTTON_START_PULLED));
const SensorEvent SignalGenerator::BUTTON_STOP( 		0b00100000<<8, "BUTTON_STOP", SWITCH_BUTTON_CLATTER_TIME , SPair(	Signalname::BUTTON_STOP_PULLED,
																															Signalname::BUTTON_STOP_PUSHED));
const SensorEvent SignalGenerator::BUTTON_RESET( 		0b01000000<<8, "BUTTON_RESET", SWITCH_BUTTON_CLATTER_TIME, SPair(	Signalname::BUTTON_RESET_PUSHED,
																															Signalname::BUTTON_RESET_PULLED));
const SensorEvent SignalGenerator::BUTTON_E_STOP(		0b10000000<<8, "BUTTON_E_STOP", E_STOP_CLATTER_TIME, SPair(	  		Signalname::BUTTON_E_STOP_PULLED,
																								  	  	  	  	  	  	 	Signalname::BUTTON_E_STOP_PUSHED));
const SensorEvent SignalGenerator::LIGHT_BARRIER_INPUT( 0b00000001, "LIGHT_BARRIER_INPUT", NOCLATTER, SPair( 				Signalname::LB_INPUT_FREED,
																								  	  	  	  	  	  	  	Signalname::LB_INPUT_INTERRUPTED));
const SensorEvent SignalGenerator::LIGHT_BARRIER_HEIGHT(0b00000010, "LIGHT_BARRIER_HEIGHT", NOCLATTER, SPair(				Signalname::LB_HEIGHT_FREED,
																								  	  	  	  	  	  	  	Signalname::LB_HEIGHT_INTERRUPTED));
const SensorEvent SignalGenerator::SENSOR_HEIGHT_MATCH(	0b00000100, "SENSOR_HEIGHT_MATCH", NOCLATTER, SPair( 				Signalname::SENSOR_HEIGHT_MATCH,
																															Signalname::SENSOR_HEIGHT_NOT_MATCH));
const SensorEvent SignalGenerator::LIGHT_BARRIER_SWITCH(0b00001000, "LIGHT_BARRIER_SWITCH", NOCLATTER, SPair(				Signalname::LB_SWITCH_FREED,
																															Signalname::LB_SWITCH_INTERRUPTED));
const SensorEvent SignalGenerator::SENSOR_METAL_MATCH(	0b00010000, "SENSOR_METAL_MATCH", NOCLATTER, SPair(  				Signalname::SENSOR_METAL_MATCH,
																								  	  	  	  	  	  	  	Signalname::SENSOR_METAL_NOT_MATCH));
const SensorEvent SignalGenerator::SENSOR_SWITCH_OPEN(	0b00100000, "SENSOR_SWITCH_OPEN", SWITCH_BUTTON_CLATTER_TIME, SPair(Signalname::SENSOR_SWITCH_IS_OPEN,
																															Signalname::SENSOR_SWITCH_IS_CLOSED));
const SensorEvent SignalGenerator::LIGHT_BARRIER_SLIDE(	0b01000000, "LIGHT_BARRIER_SLIDE", NOCLATTER,  SPair( 				Signalname::LB_SLIDE_FREED,
																								  	  	  	  	  	  	  	Signalname::LB_SLIDE_INTERRUPTED));
const SensorEvent SignalGenerator::LIGHT_BARRIER_OUTPUT(0b10000000, "LIGHT_BARRIER_OUTPUT", NOCLATTER, SPair(				Signalname::LB_OUTPUT_FREED,
																								  	  	  	  	  	  	  	Signalname::LB_OUTPUT_INTERRUPTED));


std::vector<const SensorEvent> const SignalGenerator::events = init_events();
std::chrono::steady_clock::time_point timeNow;


SignalGenerator::SignalGenerator():
running(true)
{
	LOG_SCOPE
	init_events();
	GPIO::instance().gainAccess();
	stored_mask = GPIO::instance().read(PORT::C)<<8 | GPIO::instance().read(PORT::B);
	ISR::registerISR(AsyncChannel::instance(), MAGIC_NUMBER);
	thread = std::thread(std::ref(*this));
	timeNow = std::chrono::system_clock::now();
}

SignalGenerator::~SignalGenerator() {
	LOG_SCOPE
	terminate();
	AsyncChannel::instance().sendMessage({0,0});
	thread.join();
	ISR::unregisterISR();
}

void SignalGenerator::operator()() {
	LOG_SCOPE

	while (running) {
		AsyncMsg message;
		message = AsyncChannel::instance().nextMessage();
		int current_mask = (int)message.value;
		int change = current_mask xor stored_mask;
		for(const auto &event : events) {
			if (noChatterOn(event)) {
				if (change & event.bitmask) { // change happend on event?
					if (event.bitmask & current_mask) { 	// low -> high
						pushBackOnSignalBuffer(Signal(1,1,event.signalPair.high));
					} else {						// high -> low
						pushBackOnSignalBuffer(Signal(1,1,event.signalPair.low));
					}
				}
			}
		}
		stored_mask = current_mask;
	}
}

void SignalGenerator::terminate() {
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

bool noChatterOn(SensorEvent event){
	timeNow = std::chrono::steady_clock::now();
	auto timeSinceLastInterrupt = std::chrono::duration_cast <std::chrono::milliseconds> (timeNow - event.lastTimeTriggered);
	event.lastTimeTriggered = timeNow;
	if (timeSinceLastInterrupt.count() > event.chatterProtectionTime){
		return true;
	}
	else{
		return false;
	}
}

//bool SignalGenerator::dealWithClatter(Signal signal){
//	auto timeSinceLastInterrupt = std::chrono::duration_cast <std::chrono::milliseconds> (std::chrono::steady_clock::now() - time);
//	time = std::chrono::system_clock::now();
//	if  (signal.name == Signalname::BUTTON_E_STOP_PUSHED){
//		if (timeSinceLastInterrupt.count() <= E_STOP_CLUTTER_TIME){
//			return false;
//		}
//	}
//	else if (timeSinceLastInterrupt.count() <= SWITCH_BUTTON_CLUTTER_TIME){
//		return false;
//	}
//
//	else{
//		return true;
//	}
//}

void SignalGenerator::pushBackOnSignalBuffer(Signal signal) {
	signalBuffer.push_back(signal);
}

void SignalGenerator::clearSignalBuffer() {
	LOG_SCOPE
	signalBuffer.clear();
	if(signalBuffer.size() != 0){
		LOG_ERROR<<__FUNCTION__<<": could not clear signalBuffer"<<endl;
	}
}

const std::vector<const SensorEvent> SignalGenerator::init_events() {
	LOG_SCOPE
	std::vector<const SensorEvent> events;
	events.push_back(BUTTON_START);
	events.push_back(BUTTON_STOP);
	events.push_back(BUTTON_RESET);
	events.push_back(BUTTON_E_STOP);
	events.push_back(LIGHT_BARRIER_INPUT);
	events.push_back(LIGHT_BARRIER_HEIGHT);
	events.push_back(LIGHT_BARRIER_SWITCH);
	events.push_back(LIGHT_BARRIER_SLIDE);
	events.push_back(LIGHT_BARRIER_OUTPUT);
	events.push_back(SENSOR_HEIGHT_MATCH);
	events.push_back(SENSOR_METAL_MATCH);
	events.push_back(SENSOR_SWITCH_OPEN);
	return events;
}


} /* namespace io */
} /* namespace hardwareLayer */

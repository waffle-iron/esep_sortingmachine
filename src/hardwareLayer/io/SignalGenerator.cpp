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

constexpr int MAGIC_NUMBER = 15;

namespace hardwareLayer {
namespace io {

const SensorEvent SignalGenerator::BUTTON_START(		0b00010000<<8, "BUTTON_START", SPair(	  Signalname::BUTTON_START_PUSHED,
				  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	 	  Signalname::BUTTON_START_PULLED));
const SensorEvent SignalGenerator::BUTTON_STOP( 		0b00100000<<8, "BUTTON_STOP", SPair( 	  Signalname::BUTTON_STOP_PULLED,
																							 	  Signalname::BUTTON_STOP_PUSHED));
const SensorEvent SignalGenerator::BUTTON_RESET( 		0b01000000<<8, "BUTTON_RESET", SPair(	  Signalname::BUTTON_RESET_PUSHED,
																								  Signalname::BUTTON_RESET_PULLED));
const SensorEvent SignalGenerator::BUTTON_E_STOP(		0b10000000<<8, "BUTTON_E_STOP", SPair(	  Signalname::BUTTON_E_STOP_PULLED,
																								  Signalname::BUTTON_E_STOP_PUSHED));
const SensorEvent SignalGenerator::LIGHT_BARRIER_INPUT( 0b00000001, "LIGHT_BARRIER_INPUT", SPair( Signalname::LB_INPUT_FREED,
																								  Signalname::LB_INPUT_INTERRUPTED));
const SensorEvent SignalGenerator::LIGHT_BARRIER_HEIGHT(0b00000010, "LIGHT_BARRIER_HEIGHT", SPair(Signalname::LB_HEIGHT_FREED,
																								  Signalname::LB_HEIGHT_INTERRUPTED));
const SensorEvent SignalGenerator::SENSOR_HEIGHT_MATCH(	0b00000100, "SENSOR_HEIGHT_MATCH", SPair( Signalname::SENSOR_HEIGHT_MATCH,
																								  Signalname::SENSOR_HEIGHT_NOT_MATCH));
const SensorEvent SignalGenerator::LIGHT_BARRIER_SWITCH(0b00001000, "LIGHT_BARRIER_SWITCH", SPair(Signalname::LB_SWITCH_FREED,
																								  Signalname::LB_SWITCH_INTERRUPTED));
const SensorEvent SignalGenerator::SENSOR_METAL_MATCH(	0b00010000, "SENSOR_METAL_MATCH", SPair(  Signalname::SENSOR_METAL_MATCH,
																								  Signalname::SENSOR_METAL_NOT_MATCH));
const SensorEvent SignalGenerator::SENSOR_SWITCH_OPEN(	0b00100000, "SENSOR_SWITCH_OPEN", SPair(  Signalname::SENSOR_SWITCH_IS_OPEN,
																								  Signalname::SENSOR_SWITCH_IS_CLOSED));
const SensorEvent SignalGenerator::LIGHT_BARRIER_SLIDE(	0b01000000, "LIGHT_BARRIER_SLIDE", SPair( Signalname::LB_SLIDE_FREED,
																								  Signalname::LB_SLIDE_INTERRUPTED));
const SensorEvent SignalGenerator::LIGHT_BARRIER_OUTPUT(0b10000000, "LIGHT_BARRIER_OUTPUT", SPair(Signalname::LB_OUTPUT_FREED,
																								  Signalname::LB_OUTPUT_INTERRUPTED));

std::vector<const SensorEvent> const SignalGenerator::events = init_events();


SignalGenerator::SignalGenerator():
running(true)
{
	LOG_SCOPE
	init_events();
	GPIO::instance().gainAccess();
	stored_mask = GPIO::instance().read(PORT::C)<<8 | GPIO::instance().read(PORT::B);
	ISR::registerISR(AsyncChannel::instance(), MAGIC_NUMBER);
	thread = std::thread(std::ref(*this));
}

SignalGenerator::~SignalGenerator() {
	LOG_SCOPE
	terminate();
	AsyncChannel::instance().sendMessage({0,stored_mask});
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
			if (change & event.bitmask) { // change happend on event?
				if (event.bitmask & current_mask) { 	// low -> high
					pushBackOnSignalBuffer(Signal(1,1,event.signalPair.high));
				} else {						// high -> low
					pushBackOnSignalBuffer(Signal(1,1,event.signalPair.low));
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

void SignalGenerator::pushBackOnSignalBuffer(Signal signal) {
	LOG_SCOPE

	signalBuffer.push_back(signal);
	LOG_DEBUG << "signal pushed";
	notify_observers();
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

/*
 * InterruptHandler.h
 *
 *  Created on: Oct 19, 2017
 *      Author: stammtisch
 */

#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_

#include "Signals.h"
#include <thread>
#include <vector>
#include <map>

namespace hal {
namespace io {

struct SPair {
	SPair(Signalname high, Signalname low) :
	high(high),
	low(low) {

	}
	Signalname high;
	Signalname low;
};

struct SignalBitmask {
	SignalBitmask(const int bitmask, std::string name) :
	bitmask(bitmask),
	name(name)
	{
		LOG_SCOPE
	}
	~SignalBitmask(){
		LOG_SCOPE
	}
	const int bitmask;
	std::string name;
};

class SignalGenerator {
public:
	SignalGenerator();
	virtual ~SignalGenerator();

	void operator()();
	void stop();
	Signal nextSignal();

	static SignalBitmask BUTTON_START_PUSHED;
	static SignalBitmask BUTTON_STOP_PULLED;
	static SignalBitmask BUTTON_RESET_PUSHED;
	static SignalBitmask BUTTON_E_STOP_PULLED;
	static SignalBitmask LIGHT_BARRIER_INPUT_NOT_INTERRUPTED;
	static SignalBitmask LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED;
	static SignalBitmask SENSOR_HEIGHT_MATCH;
	static SignalBitmask LIGHT_BARRIER_SWITCH_NOT_INTERRUPTED;
	static SignalBitmask SENSOR_METAL_MATCH;
	static SignalBitmask LIGHT_BARRIER_SLIDE_NOT_INTERRUPTED;
	static SignalBitmask SENSOR_SWITCH_IS_OPEN;
	static SignalBitmask LIGHT_BARRIER_OUTPUT_NOT_INTERRUPTED;

private:
	static const std::map<const int, SPair> init_map();
	static const std::map<const int, SPair> signals;
	std::thread thread;
	bool running;
	int stored_mask;
	std::vector<Signal> signalBuffer;
};

} /* namespace io */
} /* namespace hal */
#endif /* INTERRUPTHANDLER_H_ */

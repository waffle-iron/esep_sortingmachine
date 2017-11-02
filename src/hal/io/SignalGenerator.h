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

namespace hal {
namespace io {

struct SPair {
	SPair(Signalname high, Signalname low) :
	high(high),
	low(low)
	{
		LOG_SCOPE
	}
	Signalname high;
	Signalname low;
};

struct SensorEvent {
	SensorEvent(const int bitmask, std::string name, SPair signalPair) :
	bitmask(bitmask),
	name(name),
	signalPair(signalPair)
	{
		LOG_SCOPE
	}
	~SensorEvent(){
		LOG_SCOPE
	}
	const int bitmask;
	std::string name;
	SPair signalPair;
};

class SignalGenerator {
public:
	SignalGenerator();
	virtual ~SignalGenerator();

	void operator()();
	void stop();
	Signal nextSignal();

	/*
	 * @brief deletes all signals in buffers without signal SIGNAL_BUFFER_EMPTY
	 */
	void resetSignalBuffer();

	static const SensorEvent BUTTON_START;
	static const SensorEvent BUTTON_STOP;
	static const SensorEvent BUTTON_RESET;
	static const SensorEvent BUTTON_E_STOP;
	static const SensorEvent LIGHT_BARRIER_INPUT;
	static const SensorEvent LIGHT_BARRIER_HEIGHT;
	static const SensorEvent SENSOR_HEIGHT_MATCH;
	static const SensorEvent LIGHT_BARRIER_SWITCH;
	static const SensorEvent SENSOR_METAL_MATCH;
	static const SensorEvent LIGHT_BARRIER_SLIDE;
	static const SensorEvent SENSOR_SWITCH_OPEN;
	static const SensorEvent LIGHT_BARRIER_OUTPUT;

private:
	static void init_events();

	static std::vector<const SensorEvent> events;
	std::thread thread;
	bool running;
	int stored_mask;
	std::vector<Signal> signalBuffer;
};

} /* namespace io */
} /* namespace hal */
#endif /* INTERRUPTHANDLER_H_ */

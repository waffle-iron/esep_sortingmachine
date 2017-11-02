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

struct SensorEvent {
	SensorEvent(const int bitmask, std::string name) :
	bitmask(bitmask),
	name(name)
	{
		LOG_SCOPE
	}
	~SensorEvent(){
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

	/*
	 * @brief deletes all signals in buffers without signal SIGNAL_BUFFER_EMPTY
	 */
	void resetSignalBuffer();

	static SensorEvent BUTTON_START;
	static SensorEvent BUTTON_STOP;
	static SensorEvent BUTTON_RESET;
	static SensorEvent BUTTON_E_STOP;
	static SensorEvent LIGHT_BARRIER_INPUT;
	static SensorEvent LIGHT_BARRIER_HEIGHT;
	static SensorEvent SENSOR_HEIGHT_MATCH;
	static SensorEvent LIGHT_BARRIER_SWITCH;
	static SensorEvent SENSOR_METAL_MATCH;
	static SensorEvent LIGHT_BARRIER_SLIDE;
	static SensorEvent SENSOR_SWITCH_OPEN;
	static SensorEvent LIGHT_BARRIER_OUTPUT;

private:
	static const std::map<const int, SPair> init_map();
	static const std::map<const int, SPair> events;
	std::thread thread;
	bool running;
	int stored_mask;
	std::vector<Signal> signalBuffer;
};

} /* namespace io */
} /* namespace hal */
#endif /* INTERRUPTHANDLER_H_ */

/*
 * InterruptHandler.h
 *
  *  Created on: 20.10.2017
 *      Author: abj240
 */

#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_

#include "Signals.h"
#include <thread>
#include <vector>

namespace hardwareLayer {
namespace io {

/*
 * brief: SPair's high member holds signal for edge high
 * 		  SPair's low member holds signal for edge low
 */
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

/*
 * brief: SensorEvent holds data for one specific event.
 *
 * bitmask specifies specific bit for this event that consists of two signals.
 * name holds a string of the signal
 * signalPair.high holds signal for higher edge change of bit
 * siganlPair.low holds signal for lower edge  change of bit
 */
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

	/*
	 *@brief: functor for thread that listens on AsyncChannel with a blocked wait
	 */
	void operator()();

	/*
	 *@brief: terminates thread that listens on AsyncChannel within the next message
	 *@brief: that gets read after calling this method
	 */
	void terminate();

	/*
	 *@brief: returns nextSignal in signalBuffer.
	 *
	 *If signalBuffer is empty it returns Signal(cb_x,cb_x,SIGNAL_BUFFER_EMPTY)
	 */
	Signal nextSignal();

	/*
	 *@brief: pushs back Signal on signalBuffer.
	 *@param: signal Signal
	 */
	void pushBackOnSignalBuffer(Signal signal);

	/*
	 *@brief clears signalBuffer
	 */
	void clearSignalBuffer();

	bool dealWithClatter();

	// sensor events for higher byte of PORT C
	static const SensorEvent BUTTON_START;
	static const SensorEvent BUTTON_STOP;
	static const SensorEvent BUTTON_RESET;
	static const SensorEvent BUTTON_E_STOP;
	// sensor events for PORT B
	static const SensorEvent LIGHT_BARRIER_INPUT;
	static const SensorEvent LIGHT_BARRIER_HEIGHT;
	static const SensorEvent SENSOR_HEIGHT_MATCH;
	static const SensorEvent LIGHT_BARRIER_SWITCH;
	static const SensorEvent SENSOR_METAL_MATCH;
	static const SensorEvent LIGHT_BARRIER_SLIDE;
	static const SensorEvent SENSOR_SWITCH_OPEN;
	static const SensorEvent LIGHT_BARRIER_OUTPUT;

private:
	/*
	 *@brief: initializes and returns const vector<const SensorEvent> events
	 */
	static const std::vector<const SensorEvent> init_events();

	/*
	 * events holds all sensor events
	 */
	static const std::vector<const SensorEvent> events;
	std::thread thread;
	bool running;
	int stored_mask;
	std::vector<Signal> signalBuffer;
};

} /* namespace io */
} /* namespace hardwareLayer */
#endif /* INTERRUPTHANDLER_H_ */

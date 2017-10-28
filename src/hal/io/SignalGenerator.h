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

class SignalGenerator {
public:
	SignalGenerator();
	virtual ~SignalGenerator();

	void operator()();
	void stop();
	Signal nextSignal();

private:
	static const std::map<const int, SPair> init_map();
	static const std::map<const int, SPair> signals;
	std::thread thread;
	bool running;
	int stored_mask = 0;
	std::vector<Signal> signalBuffer;
};

} /* namespace io */
} /* namespace hal */
#endif /* INTERRUPTHANDLER_H_ */

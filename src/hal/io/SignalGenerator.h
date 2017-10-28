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

class SignalGenerator {
public:
	SignalGenerator();
	virtual ~SignalGenerator();

	void operator()();
	void stop();
	Signal nextSignal();

private:
	std::thread thread;
	bool running;
	int stored_mask;
	std::vector<Signal> signalBuffer;
};

} /* namespace io */
} /* namespace hal */
#endif /* INTERRUPTHANDLER_H_ */

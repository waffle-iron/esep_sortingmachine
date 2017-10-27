/*
 * InterruptHandler.h
 *
 *  Created on: Oct 19, 2017
 *      Author: stammtisch
 */

#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_

#include <thread>

namespace hal {
namespace io {

class SignalGenerator {
public:
	SignalGenerator();
	virtual ~SignalGenerator();

	void operator()();
	void stop();

private:
	std::thread thread;
	bool running;


};

} /* namespace io */
} /* namespace hal */
#endif /* INTERRUPTHANDLER_H_ */

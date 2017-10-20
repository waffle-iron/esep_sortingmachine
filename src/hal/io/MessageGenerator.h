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

class MessageGenerator {
public:
	MessageGenerator();
	virtual ~MessageGenerator();

	void operator()();
	void stop();

private:
	std::thread t_prio_low;
	bool running;


};

} /* namespace io */
} /* namespace hal */
#endif /* INTERRUPTHANDLER_H_ */

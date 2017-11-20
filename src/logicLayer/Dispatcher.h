/*
 * Dummy.h
 *
 *  Created on: 17.11.2017
 *      Author: abx724
 */

#ifndef DUMMY_H_
#define DUMMY_H_

#include "Channel.h"
#include <thread>

namespace logicLayer {

class Dispatcher {
public:
	Dispatcher(
			Channel&,
			Channel&
	);
	virtual ~Dispatcher();
	void operator()();
	void terminate();
private:
	std::thread t_;
	bool running;

	Channel& controller_;
	Channel& typeIdent_;


};

} /* namespace logicLayer */
#endif /* DUMMY_H_ */

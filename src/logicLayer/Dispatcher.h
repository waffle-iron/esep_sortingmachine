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
			Channel&
	);
	virtual ~Dispatcher();
	void operator()();
private:
	std::thread t_;

	Channel& controller_;
};

} /* namespace logicLayer */
#endif /* DUMMY_H_ */

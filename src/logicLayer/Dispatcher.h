/*
 * Dummy.h
 *
 *  Created on: 17.11.2017
 *      Author: abx724
 */

#ifndef DUMMY_H_
#define DUMMY_H_

#include "Controller.h"
#include <thread>

namespace logicLayer {

class Dispatcher {
public:
	Dispatcher();
	virtual ~Dispatcher();
	void operator()();
private:
	std::thread t_;

	Controller ctr_;
};

} /* namespace logicLayer */
#endif /* DUMMY_H_ */

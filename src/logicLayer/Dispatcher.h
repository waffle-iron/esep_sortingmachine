/*
 * Dispatcher.h
 *
 *  Created on: 13.11.2017
 *      Author: aca311
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <thread>

namespace logicLayer {

class LogicLayer;

class Dispatcher {
public:
	Dispatcher(LogicLayer& lol);
	virtual ~Dispatcher();
	virtual void operator()();
private:
	LogicLayer& lol_;
//	std::thread listing4Thread_;
};

} // end namespace

#endif /* DISPATCHER_H_ */

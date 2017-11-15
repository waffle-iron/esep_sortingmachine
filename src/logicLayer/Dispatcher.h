/*
 * Dispatcher.h
 *
 *  Created on: 13.11.2017
 *      Author: aca311
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "LogicLayer.h"

namespace logicLayer {

class Dispatcher {
public:
	explicit Dispatcher(LogicLayer&);
	virtual ~Dispatcher();
	void operator ()();
private:
	LogicLayer& lol_;
};

} // end namespace

#endif /* DISPATCHER_H_ */

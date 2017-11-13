/*
 * Dispatcher.h
 *
 *  Created on: 13.11.2017
 *      Author: aca311
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "Channel.h"

namespace logicLayer {

class Dispatcher {
public:
	explicit Dispatcher(Channel&);
	virtual ~Dispatcher();
	void operator ()();
private:
	Channel& channel;
};

} // end namespace

#endif /* DISPATCHER_H_ */

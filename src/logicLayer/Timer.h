/*
 * Timer.h
 *
 *  Created on: 13.11.2017
 *      Author: aca311
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "Channel.h"

namespace logicLayer {

class Timer {
public:
	explicit Timer(Channel&);
	virtual ~Timer();
	void operator()();
private:
	Channel& channel;
};

} // end namespace

#endif /* TIMER_H_ */

/*
 * Dispatcher.cpp
 *
 *  Created on: 13.11.2017
 *      Author: aca311
 */

#include "Dispatcher.h"
#include "Signals.h"

namespace logicLayer {

Dispatcher::Dispatcher(Channel& ch) : channel(ch) {
}

void Dispatcher::operator()(){
	Signal signal = Signal(0,0,Signalname::START_TIMERS_INPUT);
	channel<<signal;
}

Dispatcher::~Dispatcher() {
	// TODO Auto-generated destructor stub
}

} /* namespace logicLayer */

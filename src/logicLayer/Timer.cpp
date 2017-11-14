/*
 * Timer.cpp
 *
 *  Created on: 13.11.2017
 *      Author: aca311
 */

#include "Timer.h"
#include "Signals.h"

namespace logicLayer {

Timer::Timer() :
SignalReceiver::SignalReceiver()
{

}

void Timer::operator()(){
	Signal lastRead;
	while(1){
		lastRead<<channel_;
		if (lastRead.name == Signalname::START_TIMERS_INPUT) {
			cout << (int)lastRead.name <<endl;
		} else {
			cout << "Timer: kein richtiges signal erhalten" << endl;
		}
	}
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

} /* namespace logicLayer */

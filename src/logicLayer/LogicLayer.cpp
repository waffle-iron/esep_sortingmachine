/*
 * LogicLayer.cpp
 *
 *  Created on: 26.10.2017
 *      Author: abj240
 */

#include "LogicLayer.h"
#include "Timer.h"


namespace logicLayer {

LogicLayer::LogicLayer(hardwareLayer::HardwareLayer& hal)
: hal(hal)
, timer(hal)
{
	hal.register_observer(this);
}

LogicLayer::~LogicLayer() {
	// TODO Auto-generated destructor stub
}


void LogicLayer::notify(){
	Signal signal;
	while((signal = hal.getSignal()).name != Signalname::SIGNAL_BUFFER_EMPTY) {
		cout << "LogicLayer: I have been notified! Now I go get the Signal." << endl;
		switch(signal.name) {
		case Signalname::START_CHATTER_TIMER:
			timer.start_chatter_timer();
			break;
		default:
			cout << "LogicLayer: Default signal handling." << endl;
			break;
		}
	}
}
} /* namespace logicLayer */

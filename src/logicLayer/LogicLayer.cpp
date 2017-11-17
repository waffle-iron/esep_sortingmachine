/*
 * LogicLayer.cpp
 *
 *  Created on: 26.10.2017
 *      Author: abj240
 */

#include "LogicLayer.h"


namespace logicLayer {

LogicLayer::LogicLayer(hardwareLayer::HardwareLayer& hal) :
hal(hal),
dispatcher_(*new Dispatcher)
{
	hal.register_observer(this);
}

LogicLayer::~LogicLayer() {
	//delete &dispatcher_;
}


void LogicLayer::notify(){
	Signal signal;
	while((signal = hal.getSignal()).name != Signalname::SIGNAL_BUFFER_EMPTY) {
		cout << "LogicLayer: I have been notified! Now I go get the Signal." << endl;
	}
	cout << "LogicLayer: I have been notified! All signals read." << endl;
	//cout << hal.getSignal().name << endl;
}
} /* namespace logicLayer */

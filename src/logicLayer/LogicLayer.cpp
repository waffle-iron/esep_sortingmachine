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
controller_(*new Controller),
typeIdent_(*new TypeIdentification),
timer_(*new Timer),
calibration_(*new Calibration),
errorHandler_(*new ErrorHandler),
sorting_(*new Sorting),
dispatcher_(*new Dispatcher(
		controller_.getChannel(),
		typeIdent_.getChannel()
		))
{
	hal.register_observer(this);
}

LogicLayer::~LogicLayer() {
	cout << "call lol's deconstructor " << endl;
	delete &dispatcher_;
	cout << "before typeIdent" << endl;
	delete &typeIdent_;
	cout << "after typeIdent" << endl;
	delete &controller_;
	cout << "after controller" << endl;
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

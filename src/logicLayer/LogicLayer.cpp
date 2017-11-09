/*
 * LogicLayer.cpp
 *
 *  Created on: 26.10.2017
 *      Author: abj240
 */

#include "LogicLayer.h"


namespace logicLayer {

LogicLayer::LogicLayer(hardwareLayer::HardwareLayer& hal) :
hal(hal)
{
	//hal.register_observer(this);
	hal.getSignalGenerator().register_observer(this); //listen to SignalGenerator
}

LogicLayer::~LogicLayer() {
	// TODO Auto-generated destructor stub
}


void LogicLayer::notify(){
	Signal signal;

	cout << "notify called";

	while((signal = hal.getSignal()).name != Signalname::SIGNAL_BUFFER_EMPTY) {
		cout << "LogicLayer: I have been notified! Now I go get the Signal." << endl;

		switch(signal.name){
			case Signalname::BLINK_GREEN_FAST:
				hal.blinkGreen(Speed::fast);
			break;
			case Signalname::CONNECTION_LOST:
				hal.blinkRed(Speed::slow);
			break;
			default:
			break;
		}

	}
	cout << "LogicLayer: I have been notified! All signals read." << endl;
	//cout << hal.getSignal().name << endl;
}
} /* namespace logicLayer */

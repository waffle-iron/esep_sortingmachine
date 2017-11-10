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
		switch(signal.name){
			case Signalname::BLINK_GREEN_FAST:
				hal.blinkGreen(Speed::fast);
			break;
			case Signalname::CONNECTION_LOST:
				hal.blinkRed(Speed::slow);
			break;
			case Signalname::CONNECTION_CONNECTED:
				hal.redLightOff();
			break;
			default:
			break;
		}

	}
	//cout << hal.getSignal().name << endl;
}
} /* namespace logicLayer */

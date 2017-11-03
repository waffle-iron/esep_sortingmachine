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
	hal.register_observer(this);
}

LogicLayer::~LogicLayer() {
	// TODO Auto-generated destructor stub
}


void LogicLayer::notify(){
	cout << "LogicLayer: I have been notified! Now I go get the Signal." << endl;
	cout << hal.getSignal() << endl;

}
} /* namespace logicLayer */

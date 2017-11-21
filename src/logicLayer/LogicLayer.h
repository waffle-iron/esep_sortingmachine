/*
 * LogicLayer.h
 *
 *  Created on: 26.10.2017
 *      Author: abj240
 */

#ifndef LOGICLAYER_H_
#define LOGICLAYER_H_

#include "Observer.h"
#include "HardwareLayer.h"
#include "SensorTest.h"

namespace logicLayer {

class LogicLayer : public Observer {
public:
	LogicLayer(hardwareLayer::HardwareLayer&);
	virtual ~LogicLayer();
	void notify();
private:
	hardwareLayer::HardwareLayer& hal;
	SensorTest sensorTest;
};

} /* namespace logicLayer */

#endif /* LOGICLAYER_H_ */

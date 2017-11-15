/*
 * LogicLayer.h
 *
 *  Created on: 26.10.2017
 *      Author: abj240
 */

#ifndef LOGICLAYER_H_
#define LOGICLAYER_H_

#include "Dispatcher.h"

#include "Observer.h"
#include "HardwareLayer.h"



namespace logicLayer {

class LogicLayer : public Observer {
public:
	LogicLayer(hardwareLayer::HardwareLayer&);
	virtual ~LogicLayer();
	void notify();
private:
	hardwareLayer::HardwareLayer& hal;
	Dispatcher dispatcher_;
};

} /* namespace logicLayer */

#endif /* LOGICLAYER_H_ */

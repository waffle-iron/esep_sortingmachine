/*
 * LogicLayer.h
 *
 *  Created on: 26.10.2017
 *      Author: abj240
 */

#ifndef LOGICLAYER_H_
#define LOGICLAYER_H_

#include "Observer.h"
#include "HAL.h"

namespace logicLayer {

class LogicLayer : public Observer {
public:
	LogicLayer(hal::HAL&);
	virtual ~LogicLayer();
	void notify();
private:
	hal::HAL& hal;
};

} /* namespace logicLayer */

#endif /* LOGICLAYER_H_ */

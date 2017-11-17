/*
 * Controller.h
 *
 *  Created on: 15.11.2017
 *      Author: abx724
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "SignalReceiver.h"

namespace logicLayer {

class Controller: public logicLayer::SignalReceiver {
public:
	Controller();
	virtual ~Controller();

	void operator()();
};

} /* namespace logicLayer */
#endif /* CONTROLLER_H_ */

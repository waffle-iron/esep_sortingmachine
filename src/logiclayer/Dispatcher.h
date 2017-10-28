/*
 * Dispatcher.h
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "Header.h"
#include "Controller.h"
#include "Sorting.h"
#include <vector>

namespace logicLayer {

class Dispatcher {
public:
	Dispatcher();
	virtual ~Dispatcher();
	void subscribe(controller::Controller* controller);
	void unsubscibe(controller::Controller* controller);
	void sendToControllers(Signal signal); // all lb_signal
private:
	Sorting sorting;
	std::vector<controller::Controller*> controllers;
};

} /* namespace logicLayer */
#endif /* DISPATCHER_H_ */

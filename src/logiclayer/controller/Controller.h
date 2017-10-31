/*
 * Controller.h
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Header.h"
#include "HAL.h"
#include <vector>

namespace logicLayer {
namespace controller {

/* @brief Controller can handle all light barrier signals
 *
 */
class Controller {
public:
	Controller(hal::HAL& hal);
	virtual ~Controller();

	/*
	 * @brief method gets called in thread and is a blocked waiting call for new async signals from channel
	 */
	Signal getSignal();

	/*
	 * @brief method gets called when thread is started with an Controller Object
	 */
    void operator()();

    /*
     * @brief provokes termination of thread the next time a signal gets read from channel
     */
    void terminate();

	/*
	 * @brief gets called from derived classes like ItemController and performs signals
	 * like MOTOR_FORWARD_RUN_FAST calling adequate methods on hal.
	 */
	void sendSignal(Signal signal);

	/*
	 * @brief adds controller to controllers vector if not already in
	 */
	void registerController(Controller* controller);

	/*
	 * @brief removes controller from controllers vector if not already removed
	 */
	void unregisterController(Controller* controller);

private:
	hal::HAL& hal;
	bool running;
	std::vector<Controller*> controllers;
};

} /* namespace controller */
} /* namespace logicLayer */
#endif /* CONTROLLER_H_ */

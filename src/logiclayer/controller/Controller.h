/*
 * Controller.h
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Header.h"

namespace logicLayer {
namespace controller {

/* @brief Controller can handle all light barrier signals
 *
 */
class Controller {
public:
	Controller();
	virtual ~Controller();
	Signal getSignal();
	void sendSignal(Signal signal);
};

} /* namespace controller */
} /* namespace logicLayer */
#endif /* CONTROLLER_H_ */

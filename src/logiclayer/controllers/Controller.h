/*
 * Controller.h
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

namespace logicLayer {
namespace controllers {

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

} /* namespace controllers */
} /* namespace logicLayer */
#endif /* CONTROLLER_H_ */

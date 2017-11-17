/*
 * ErrorController.h
 *
 *  Created on: 15.11.2017
 *      Author: abx724
 */

#ifndef ERRORCONTROLLER_H_
#define ERRORCONTROLLER_H_

#include "SignalReceiver.h"

namespace logicLayer {

class ErrorController: public logicLayer::SignalReceiver {
public:
	ErrorController();
	virtual ~ErrorController();
	void operator()();
};

} /* namespace logicLayer */
#endif /* ERRORCONTROLLER_H_ */

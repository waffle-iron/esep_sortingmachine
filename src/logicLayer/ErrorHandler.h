/*
 * ErrorHandler.h
 *
 *  Created on: 20.11.2017
 *      Author: abx724
 */

#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_

#include "SignalReceiver.h"

namespace logicLayer {

class ErrorHandler: public logicLayer::SignalReceiver {
public:
	ErrorHandler();
	virtual ~ErrorHandler();
	void operator()();
};

} /* namespace logicLayer */
#endif /* ERRORHANDLER_H_ */

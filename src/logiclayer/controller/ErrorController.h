/*
 * Errorcontroller.h
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */
#include "Header.h"
#include "Controller.h";
#include "HAL.h"

#ifndef ERRORCONTROLLER_H_
#define ERRORCONTROLLER_H_

namespace logicLayer {
namespace controller {

class ErrorController : public Controller {
public:
	ErrorController(hal::HAL& hal);
	virtual ~ErrorController();
};

} /* namespace controller */
} /* namespace logicLayer */
#endif /* ERRORCONTROLLER_H_ */

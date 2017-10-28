/*
 * Errorcontroller.h
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */
#include "Header.h"
#include "Controller.h";

#ifndef ERRORCONTROLLER_H_
#define ERRORCONTROLLER_H_

namespace logicLayer {
namespace controller {

class Errorcontroller : public Controller {
public:
	Errorcontroller();
	virtual ~Errorcontroller();
};

} /* namespace controller */
} /* namespace logicLayer */
#endif /* ERRORCONTROLLER_H_ */

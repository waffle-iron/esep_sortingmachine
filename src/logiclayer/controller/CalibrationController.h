/*
 * CalibrationController.h
 *
 *  Created on: Oct 31, 2017
 *      Author: stammtisch
 */

#ifndef CALIBRATIONCONTROLLER_H_
#define CALIBRATIONCONTROLLER_H_

#include "Controller.h"

namespace logicLayer {
namespace controller {

class CalibrationController : public Controller{
public:
	CalibrationController(hal::HAL& hal);
	virtual ~CalibrationController();

};

} /* namespace controller */
} /* namespace logicLayer */
#endif /* CALIBRATIONCONTROLLER_H_ */

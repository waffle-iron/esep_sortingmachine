/*
 * CalibrationController.h
 *
 *  Created on: 15.11.2017
 *      Author: abx724
 */

#ifndef CALIBRATIONCONTROLLER_H_
#define CALIBRATIONCONTROLLER_H_

#include "SignalReceiver.h"

namespace logicLayer {

class CalibrationController: public logicLayer::SignalReceiver {
public:
	CalibrationController();
	virtual ~CalibrationController();
	void operator()();
};

} /* namespace logicLayer */
#endif /* CALIBRATIONCONTROLLER_H_ */
